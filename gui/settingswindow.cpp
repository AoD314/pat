
#include "settingswindow.hpp"
#include "settings.hpp"

SettingsWindow::SettingsWindow(Settings * set, QWidget *parent)
{
	settings = set;
	box_v = new QVBoxLayout;

	box_h_l = new QHBoxLayout;
	box_h_b = new QHBoxLayout;

	lbl_lang = new QLabel(tr("Language"));
	list_lang = new QComboBox();
	list_lang->addItem("en");
	list_lang->addItem("ru");

	box_h_l->addWidget(lbl_lang);
	box_h_l->addWidget(list_lang);

	btn_save = new QPushButton(tr("Save"));
	btn_cancel = new QPushButton(tr("Cancel"));

	connect(btn_save, SIGNAL(clicked()), this, SLOT(save_settings()));
	connect(btn_cancel, SIGNAL(clicked()), this, SLOT(cancel()));

	box_h_b->addWidget(btn_save);
	box_h_b->addStretch(1);
	box_h_b->addWidget(btn_cancel);

	box_v->addLayout(box_h_l);
	box_v->addLayout(box_h_b);

	setWindowTitle(tr("Settings"));
	setLayout(box_v);
}

void SettingsWindow::save_settings()
{
	char ** c;
	settings->set_language(list_lang->currentText());

	QTranslator trans;
	trans.load(settings->language() + ".qm", settings->get_path_to_language());
	qApp->installTranslator(&trans);

	settings->SaveSettings();

	close();
}

void SettingsWindow::cancel()
{
	close();
}

