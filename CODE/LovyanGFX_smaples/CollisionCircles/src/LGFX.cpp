#include "LGFX.h"

LGFX::LGFX(void)
{
    {                                      // バス制御の設定を行います。
        auto cfg = _bus_instance.config(); // バス設定用の構造体を取得します。
        cfg.spi_host = VSPI_HOST;          // 使用するSPIを選択  ESP32-S2,C3 : SPI2_HOST or SPI3_HOST / ESP32 : VSPI_HOST or HSPI_HOST
        cfg.spi_mode = 0;                  // SPI通信モードを設定 (0 ~ 3)
        cfg.freq_write = 20000000;
        cfg.freq_read = 16000000;               // 受信時のSPIクロック
        cfg.spi_3wire = true;                   // 受信をMOSIピンで行う場合はtrueを設定
        cfg.use_lock = true;                    // トランザクションロックを使用する場合はtrueを設定
        cfg.dma_channel = SPI_DMA_CH_AUTO;      // 使用するDMAチャンネルを設定 (0=DMA不使用 / 1=1ch / 2=ch / SPI_DMA_CH_AUTO=自動設定)
        cfg.pin_sclk = 18;                      // SPIのSCLKピン番号を設定
        cfg.pin_mosi = 22;                      // SPIのMOSIピン番号を設定
        cfg.pin_miso = -1;                      // SPIのMISOピン番号を設定 (-1 = disable)
        cfg.pin_dc = 27;                        // SPIのD/Cピン番号を設定  (-1 = disable)
        _bus_instance.config(cfg);              // 設定値をバスに反映します。
        _panel_instance.setBus(&_bus_instance); // バスをパネルにセットします。
    }

    {                                        // 表示パネル制御の設定を行います。
        auto cfg = _panel_instance.config(); // 表示パネル設定用の構造体を取得します。
        cfg.pin_cs = 14;                     // CSが接続されているピン番号   (-1 = disable)
        cfg.pin_rst = 33;                    // RSTが接続されているピン番号  (-1 = disable)
        cfg.pin_busy = -1;                   // BUSYが接続されているピン番号 (-1 = disable)

        cfg.invert = true;
        cfg.rgb_order = false;

        cfg.memory_width = 128;
        cfg.memory_height = 160;

        cfg.panel_width = 80;   // 実際に表示可能な幅
        cfg.panel_height = 160; // 実際に表示可能な高さ
        cfg.offset_x = 24;      // パネルのX方向オフセット量
        cfg.offset_y = 0;       // パネルのY方向オフセット量
        _panel_instance.config(cfg);
    }
    setPanel(&_panel_instance); // 使用するパネルをセットします。
}