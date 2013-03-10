#include "PresetComboBox.h"

// ================= Private methods =================

void PresetComboBox::updateList()
{
	while(this->count()>0)
		this->removeItem(0);

	for(unsigned int i=0;i<presets->size();i++)
	{
		this->addItem(presets->at(i)->getName());
	}

	savePresets();
}

void PresetComboBox::loadPresets()
{
	QString		 fileString;
	QStringList  presetList, valuesList;
	Preset	    *p;
	unsigned int count;
	
	QFile file(PRESET_FILE);
	if(file.open(QIODevice::ReadOnly))
	{
		QTextStream in(&file);
		// Read in the whole data series file into one string
		while(!in.atEnd()) fileString.append(in.readLine());
	}
	file.close();

	presetList = fileString.split(SEP_PRESET);
	for(unsigned int i=0;i<presetList.size();i++)
	{
		valuesList = presetList.at(i).split(SEP_VALUE);
		if(valuesList.size()!=21	 ) continue;
		if(valuesList.at(0).isEmpty()) continue;

		presets->push_back(new Preset());
		p = presets->back();

		p->setName(valuesList.at(0));

		count = 1;
		for(unsigned int j=0;j<NUM_SIDES;j++)
			for(unsigned int k=0;k<NUM_BRANCHES;k++)
				for(unsigned int l=0;l<NUM_COLORS;l++)
					p->setColor(j, k, l, (unsigned char) valuesList.at(count++).toUInt());

		p->setWhite(SIDE_TOP, (unsigned char) valuesList.at(19).toUInt());
		p->setWhite(SIDE_BOT, (unsigned char) valuesList.at(20).toUInt());
	}
}

void PresetComboBox::savePresets()
{
	QFile file(PRESET_FILE);
	if(file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
	{
		Preset *p;
		QTextStream out(&file);
		for(unsigned int i=0;i<presets->size();i++)
		{
			p = presets->at(i);
			out << p->getName() << SEP_VALUE << flush;
			for(unsigned int j=0;j<NUM_SIDES;j++)
				for(unsigned int k=0;k<NUM_BRANCHES;k++)
					for(unsigned int l=0;l<NUM_COLORS;l++)
						out << p->colorValue(j, k, l) << SEP_VALUE << flush;

			out << p->whiteValue(0) << SEP_VALUE << p->whiteValue(1) << flush;

			if(i<presets->size()-1) out << SEP_PRESET << endl;
		}
	}
	file.close();
}

// ================= Constructor / Destructor =================

PresetComboBox::PresetComboBox(LedState *getLst, QWidget *parent) : QComboBox(parent)
{
	lst		= getLst;
	presets = new vector<Preset*>;

	loadPresets();
	updateList ();

	QObject::connect(this, SIGNAL(activated(int)), this, SLOT(setPreset(int)));
}

PresetComboBox::~PresetComboBox()
{
	for(unsigned int i=0;i<presets->size();i++) delete(presets->at(i));
	presets->clear();
	delete(presets); presets = NULL;
}

// ================= Public methods =================

void PresetComboBox::savePreset(QString name)
{
	Preset *p;
	QString checkName = name;
	checkName.replace(SEP_PRESET, "");
	checkName.replace(SEP_VALUE , "");
	
	if(checkName.isEmpty())
	{
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setText("Invalid preset name");
		msgBox.exec   (						);
		setPresetName (checkName			);
		return;
	}
	if(nameExists(checkName)==-1)
	{
		presets->push_back(new Preset());
		p = presets->back();
	}
	else
	{
		p = presets->at(nameExists(checkName));
	}

	if(p==NULL) return;

	p->setName(checkName);
	for(unsigned int i=0;i<NUM_SIDES;i++)
	{
		p->setWhite(i, lst->getWhite(i));
		for(unsigned int j=0;j<NUM_BRANCHES;j++)
		{
			p->setColor(i, j, COLOR_RED  , lst->getRed  (i, j));
			p->setColor(i, j, COLOR_GREEN, lst->getGreen(i, j));
			p->setColor(i, j, COLOR_BLUE , lst->getBlue (i, j));
		}
	}
	updateList();
	setPresetName("");
}

void PresetComboBox::discardPreset()
{
	delete(presets->at(this->currentIndex()));

	presets->erase(presets->begin()+this->currentIndex());

	updateList();
}

int PresetComboBox::nameExists(QString name)
{
	for(unsigned int i=0;i<presets->size();i++)
		if(presets->at(i)->getName().trimmed()==name.trimmed()) return i;

	return -1;
}

// ================= Public slots =================

void PresetComboBox::setPreset(int index)
{
	Preset *p = presets->at(index);
	for(unsigned int i=0;i<NUM_SIDES;i++)
	{
		setPresetWhite(p->whiteValue(i), i*SIDE_BOTTOM);
		for(unsigned int j=0;j<NUM_BRANCHES;j++)
		{
			setPresetColor(COLOR_RED_SW  , p->colorValue(i, j, COLOR_RED  ), i*SIDE_BOTTOM, j);
			setPresetColor(COLOR_GREEN_SW, p->colorValue(i, j, COLOR_GREEN), i*SIDE_BOTTOM, j);
			setPresetColor(COLOR_BLUE_SW , p->colorValue(i, j, COLOR_BLUE ), i*SIDE_BOTTOM, j);
		}
	}


}