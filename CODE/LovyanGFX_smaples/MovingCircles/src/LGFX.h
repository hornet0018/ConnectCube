#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device
{
    lgfx::Bus_SPI _bus_instance;
    lgfx::Panel_ST7735S _panel_instance;

public:
    LGFX(void);
};