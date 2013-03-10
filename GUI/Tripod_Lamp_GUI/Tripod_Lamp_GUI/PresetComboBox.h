#ifndef PRESETCOMBOBOX_H
#define PRESETCOMBOBOX_H

#include <QFile>
#include <QComboBox>
#include <QMessageBox>
#include <QTextStream>
#include <vector>

#include "Preset.h"
#include "LEDState.h"
#include "CommandDefs.h"

#define PRESET_FILE		"presets.tlr"
#define SEP_PRESET		"|PRESET|"
#define SEP_VALUE		"|V|"

using namespace std;

class PresetComboBox : public QComboBox
{
	Q_OBJECT

private:
	LedState		*lst;
	vector<Preset*> *presets;

	void updateList();
	void loadPresets();
	void savePresets();

public:
	PresetComboBox(LedState *getLst, QWidget *parent = 0);
	virtual ~PresetComboBox();

	void savePreset	  (QString name);
	void discardPreset();
	int  nameExists(QString name);

public slots:
	void setPreset(int index);

signals:
	void setPresetColor(char, char, char, char);
	void setPresetWhite(char, char);
	void setPresetName (QString);
};

#endif // PRESETCOMBOBOX_H