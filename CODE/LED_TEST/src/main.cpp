#include <LovyanGFX.hpp>
struct LGFX_Config
{
  static constexpr spi_host_device_t spi_host = VSPI_HOST;
  static constexpr int dma_channel = 1;
  static constexpr int spi_sclk = 18;
  static constexpr int spi_mosi = 23;
  static constexpr int spi_miso = -1;
  static constexpr int spi_dlen = 8;
};

static lgfx::LGFX_SPI<LGFX_Config> lcd;
static lgfx::Panel_ST7735S panel;

//=====================setup==========================================
void setup()
{
  panel.freq_write = 20000000;
  panel.freq_fill = 27000000;
  panel.freq_read = 16000000;

  panel.spi_mode = 0;
  panel.spi_mode_read = 0;

  panel.len_dummy_read_pixel = 8;

  panel.spi_read = true;
  panel.spi_3wire = false;

  panel.spi_cs = 14;
  panel.spi_dc = 27;
  panel.gpio_rst = 33;

  panel.gpio_bl = 32;
  panel.pwm_ch_bl = 7;
  panel.backlight_level = true;

  panel.invert = true;
  panel.reverse_invert = true;
  panel.rgb_order = false;

  panel.memory_width = 128;
  panel.memory_height = 160;
  panel.panel_width = 80;
  panel.panel_height = 160;
  panel.offset_x = 24;
  panel.offset_y = 0;

  panel.rotation = 0;
  panel.offset_rotation = 0;

  lcd.setPanel(&panel);

  SPIFFS.begin();

  lcd.init();

  lcd.setRotation(2);
  lcd.setColorDepth(24);
  lcd.fillScreen(0);

  //------------------------------------------------------

  // lcd.drawJpgFile(SPIFFS, "/test.jpg", 0, 0);
}
//============================================================
void loop(void)
{
}