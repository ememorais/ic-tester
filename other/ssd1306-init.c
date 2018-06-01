/**
 * according to http://www.adafruit.com/datasheets/UG-2864HSWEG01.pdf Chapter 4.4 Page 15
 */
void ssd1306Init(void)
{
    i2c_OLED_send_cmd(0xAE); // Set display OFF		
 
    i2c_OLED_send_cmd(0xD4); // Set Display Clock Divide Ratio / OSC Frequency
    i2c_OLED_send_cmd(0x80); // Display Clock Divide Ratio / OSC Frequency 
 
    i2c_OLED_send_cmd(0xA8); // Set Multiplex Ratio
    i2c_OLED_send_cmd(0x3F); // Multiplex Ratio for 128x64 (64-1)
 
    i2c_OLED_send_cmd(0xD3); // Set Display Offset
    i2c_OLED_send_cmd(0x00); // Display Offset
 
    i2c_OLED_send_cmd(0x40); // Set Display Start Line
 
    i2c_OLED_send_cmd(0x8D); // Set Charge Pump
    i2c_OLED_send_cmd(0x14); // Charge Pump (0x10 External, 0x14 Internal DC/DC)
 
    i2c_OLED_send_cmd(0xA1); // Set Segment Re-Map
    i2c_OLED_send_cmd(0xC8); // Set Com Output Scan Direction
 
    i2c_OLED_send_cmd(0xDA); // Set COM Hardware Configuration
    i2c_OLED_send_cmd(0x12); // COM Hardware Configuration
 
    i2c_OLED_send_cmd(0x81); // Set Contrast
    i2c_OLED_send_cmd(0xCF); // Contrast
 
    i2c_OLED_send_cmd(0xD9); // Set Pre-Charge Period
    i2c_OLED_send_cmd(0xF1); // Set Pre-Charge Period (0x22 External, 0xF1 Internal)
 
    i2c_OLED_send_cmd(0xDB); // Set VCOMH Deselect Level
    i2c_OLED_send_cmd(0x40); // VCOMH Deselect Level
 
    i2c_OLED_send_cmd(0xA4); // Set all pixels OFF
    i2c_OLED_send_cmd(0xA6); // Set display not inverted
    i2c_OLED_send_cmd(0xAF); // Set display On
	
    i2c_OLED_clear_display();
}