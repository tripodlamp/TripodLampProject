#ifndef LED_H
#define LED_H

class Led
{
private:
	unsigned char m_red, m_green, m_blue, m_white;

public:
	Led()
	{
		m_red   = 0x00;
		m_green = 0x00;
		m_blue  = 0x00;
		m_white = 0x00;
	}

	virtual ~Led() {  }

	unsigned char red  () { return m_red  ; }
	unsigned char green() { return m_green; }
	unsigned char blue () { return m_blue ; }
	unsigned char white() { return m_white; }

	void setRed  (unsigned char v) { m_red   = v; }
	void setGreen(unsigned char v) { m_green = v; }
	void setBlue (unsigned char v) { m_blue  = v; }
	void setWhite(unsigned char v) { m_white = v; }
};

#endif // LED_H