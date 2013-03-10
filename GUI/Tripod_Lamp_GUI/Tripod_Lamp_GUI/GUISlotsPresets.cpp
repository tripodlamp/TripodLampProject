#include "tripod_lamp_gui.h"

void Tripod_Lamp_GUI::setUpPresetComboBox()
{
	presetBox = new PresetComboBox(lst, ui.verticalLayoutWidget_2);
	ui.vLayoutPreset->addWidget(presetBox);
	presetBox->setVisible(true);

	QObject::connect(ui.pushButtonPresetSave   , SIGNAL(clicked		 ()), this, SLOT(savePreset   ()));
	QObject::connect(ui.lineEditPresetName     , SIGNAL(returnPressed()), this, SLOT(savePreset   ()));
	QObject::connect(ui.pushButtonPresetDiscard, SIGNAL(clicked		 ()), this, SLOT(discardPreset()));
	QObject::connect(presetBox				   , SIGNAL(setPresetColor(char, char, char, char)), this, SLOT(setPresetColor(char, char, char, char)));
	QObject::connect(presetBox				   , SIGNAL(setPresetWhite(char, char			 )), this, SLOT(setPresetWhite(char, char			 )));
}

void Tripod_Lamp_GUI::savePreset()
{
	if(!ui.checkBoxPresetAskOverwrite->isChecked() && presetBox->nameExists(ui.lineEditPresetName->text())!=-1)
	{
		int ret = QMessageBox::warning(this, tr("Save preset"), tr("Preset with the name '"+ui.lineEditPresetName->text()+"' already exists.\nOverwrite it?"), QMessageBox::Yes | QMessageBox::Cancel);
		if(ret==QMessageBox::Cancel) return;
	}

	presetBox->savePreset(ui.lineEditPresetName->text());
}

void Tripod_Lamp_GUI::discardPreset() { presetBox->discardPreset(); }

void Tripod_Lamp_GUI::setPresetColor(char color, char colorValue, char side, char branch)
{
	if(ui.pushButtonConnect->text()=="Disconnect")
		cmg->setLED(color, colorValue, side, branch);
}

void Tripod_Lamp_GUI::setPresetWhite(char colorValue, char side)
{
	if(ui.pushButtonConnect->text()=="Disconnect")
		cmg->setWhite(colorValue, true, side);
}

void Tripod_Lamp_GUI::setPresetName(QString name)
{
	ui.lineEditPresetName->setText(name);
}