// ============================================================
// MICRO SD IMPLEMENTATION
// verwaltet SD Karte, Dateien und einfache Dateizugriffe
// ============================================================

#include "micro_sd.h"

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#include "../../include/pins.h"
#include "../Debug/logger.h"

// merkt sich ob die SD erfolgreich gestartet wurde
static bool microSDReady = false;

// ------------------------------------------------------------
// prueft ueber den Card Detect Pin ob eine Karte steckt
// viele Module ziehen CD bei eingesteckter Karte auf LOW
// ------------------------------------------------------------
bool isMicroSDInserted()
{
    pinMode(SD_CD, INPUT_PULLUP);

    // LOW = Karte erkannt
    return digitalRead(SD_CD) == LOW;
}

// ------------------------------------------------------------
// startet die micro SD Karte
// ------------------------------------------------------------
bool initMicroSD()
{
    log(INFO, "Starte micro SD");

    // Card Detect Pin vorbereiten
    pinMode(SD_CD, INPUT_PULLUP);

    // Hinweis falls keine Karte erkannt wird
    if (!isMicroSDInserted())
    {
        log(WARN, "Card Detect meldet keine Karte");
    }

    // SPI mit deinen verdrahteten Pins starten
    SPI.begin(SD_CLK, SD_DO, SD_DI, SD_CS);

    // SD starten
    if (!SD.begin(SD_CS, SPI))
    {
        microSDReady = false;
        log(ERROR, "micro SD konnte nicht gestartet werden");
        return false;
    }

    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        microSDReady = false;
        log(ERROR, "Keine micro SD Karte erkannt");
        return false;
    }

    microSDReady = true;

    log(SUCCESS, "micro SD bereit");
    printMicroSDInfo();

    return true;
}

// ------------------------------------------------------------
// prueft ob die SD erfolgreich gestartet wurde
// ------------------------------------------------------------
bool isMicroSDReady()
{
    return microSDReady;
}

// ------------------------------------------------------------
// gibt Infos ueber die SD im Log aus
// ------------------------------------------------------------
void printMicroSDInfo()
{
    if (!microSDReady)
    {
        log(WARN, "micro SD nicht bereit");
        return;
    }

    uint8_t cardType = SD.cardType();
    uint64_t cardSizeMB = SD.cardSize() / (1024ULL * 1024ULL);

    String typeText = "unbekannt";

    if (cardType == CARD_MMC)  typeText = "MMC";
    if (cardType == CARD_SD)   typeText = "SDSC";
    if (cardType == CARD_SDHC) typeText = "SDHC/SDXC";

    log(INFO, "SD Typ", typeText);
    log(INFO, "SD Groesse MB", (unsigned long)cardSizeMB);
}

// ------------------------------------------------------------
// listet Dateien in einem Ordner auf
// ------------------------------------------------------------
void listMicroSDDir(const char* path, uint8_t levels)
{
    if (!microSDReady)
    {
        log(WARN, "micro SD nicht bereit");
        return;
    }

    File root = SD.open(path);

    if (!root)
    {
        log(ERROR, "Ordner konnte nicht geoeffnet werden", path);
        return;
    }

    if (!root.isDirectory())
    {
        log(ERROR, "Pfad ist kein Ordner", path);
        root.close();
        return;
    }

    log(INFO, "Liste Ordner", path);

    File file = root.openNextFile();

    while (file)
    {
        if (file.isDirectory())
        {
            log(INFO, "DIR", file.name());

            if (levels > 0)
            {
                String childPath = String(path);

                if (!childPath.endsWith("/"))
                {
                    childPath += "/";
                }

                childPath += file.name();

                listMicroSDDir(childPath.c_str(), levels - 1);
            }
        }
        else
        {
            log(INFO, "FILE", String(file.name()) + " (" + String(file.size()) + " bytes)");
        }

        file = root.openNextFile();
    }

    root.close();
}

// ------------------------------------------------------------
// schreibt eine Datei neu
// ------------------------------------------------------------
bool writeTextFile(const char* path, const String& content)
{
    if (!microSDReady)
    {
        log(WARN, "micro SD nicht bereit");
        return false;
    }

    // vorhandene Datei zuerst loeschen
    if (SD.exists(path))
    {
        SD.remove(path);
    }

    File file = SD.open(path, FILE_WRITE);

    if (!file)
    {
        log(ERROR, "Datei konnte nicht zum Schreiben geoeffnet werden", path);
        return false;
    }

    size_t written = file.print(content);
    file.close();

    if (written == 0)
    {
        log(ERROR, "Nichts in Datei geschrieben", path);
        return false;
    }

    log(SUCCESS, "Datei geschrieben");
    log(INFO, "Pfad", path);

    return true;
}

// ------------------------------------------------------------
// ueberschreibt eine Datei komplett
// ------------------------------------------------------------
bool overwriteTextFile(const char* path, const String& content)
{
    return writeTextFile(path, content);
}

// ------------------------------------------------------------
// haengt Text an eine Datei an
// ------------------------------------------------------------
bool appendTextFile(const char* path, const String& content)
{
    if (!microSDReady)
    {
        log(WARN, "micro SD nicht bereit");
        return false;
    }

    File file = SD.open(path, FILE_APPEND);

    if (!file)
    {
        log(ERROR, "Datei konnte nicht zum Anhaengen geoeffnet werden", path);
        return false;
    }

    size_t written = file.print(content);
    file.close();

    if (written == 0)
    {
        log(ERROR, "Nichts an Datei angehaengt", path);
        return false;
    }

    log(SUCCESS, "Text an Datei angehaengt");
    log(INFO, "Pfad", path);

    return true;
}

// ------------------------------------------------------------
// liest eine Textdatei komplett
// ------------------------------------------------------------
String readTextFile(const char* path)
{
    if (!microSDReady)
    {
        log(WARN, "micro SD nicht bereit");
        return "";
    }

    File file = SD.open(path, FILE_READ);

    if (!file)
    {
        log(ERROR, "Datei konnte nicht gelesen werden", path);
        return "";
    }

    String content = "";

    while (file.available())
    {
        content += static_cast<char>(file.read());
    }

    file.close();

    log(SUCCESS, "Datei gelesen");
    log(INFO, "Pfad", path);

    return content;
}

// ------------------------------------------------------------
// loescht eine Datei
// ------------------------------------------------------------
bool deleteFile(const char* path)
{
    if (!microSDReady)
    {
        log(WARN, "micro SD nicht bereit");
        return false;
    }

    if (!SD.exists(path))
    {
        log(WARN, "Datei existiert nicht", path);
        return false;
    }

    if (!SD.remove(path))
    {
        log(ERROR, "Datei konnte nicht geloescht werden", path);
        return false;
    }

    log(SUCCESS, "Datei geloescht");
    log(INFO, "Pfad", path);

    return true;
}

// ------------------------------------------------------------
// prueft ob eine Datei existiert
// ------------------------------------------------------------
bool fileExists(const char* path)
{
    if (!microSDReady)
    {
        return false;
    }

    return SD.exists(path);
}

// ------------------------------------------------------------
// gibt die Dateigroesse zurueck
// ------------------------------------------------------------
size_t getFileSize(const char* path)
{
    if (!microSDReady)
    {
        return 0;
    }

    File file = SD.open(path, FILE_READ);

    if (!file)
    {
        return 0;
    }

    size_t size = file.size();
    file.close();

    return size;
}