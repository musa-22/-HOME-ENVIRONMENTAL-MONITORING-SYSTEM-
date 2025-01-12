#include <TFT_eSPI.h>
// lightly pilfered from https://github.com/Bodmer/TFT_eSPI/tree/master/examples/160%20x%20128/TFT_Meter_5

#define M_SIZE 0.667
#define TFT_GREY 0x5AEB
#define TFT_ORANGE 0xFD20 /* 255, 165,   0 */

class AnalogueMeter
{
private:
    TFT_eSPI *tft;
    float ltx = 0;                                   // Saved x coord of bottom of needle
    uint16_t osx = M_SIZE * 120, osy = M_SIZE * 120; // Saved x & y coords

    int old_analog = -999; // Value last displayed

    int value[6] = {0, 0, 0, 0, 0, 0};
    int old_value[6] = {-1, -1, -1, -1, -1, -1};
    int d = 0;

public:
    AnalogueMeter(TFT_eSPI* tft);
    void plotNeedle(String label, int value, byte ms_delay);
    void analogMeter();
};