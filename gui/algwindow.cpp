
#include "algwindow.hpp"

AlgWindow::AlgWindow(QWidget * parent) : QWidget(parent)
{
	box_h = new QVBoxLayout;
	box_h_b = new QHBoxLayout;
	box_v = new QVBoxLayout;

	lbl_alg = new QLabel(tr("Algorithm") + ":");
	list_alg = new QComboBox;
	list_alg->addItem(tr("brute force"));
	list_alg->addItem(tr("gradient"));

	lbl_count = new QLabel(tr("Max count of iterations") + ":");
	spin_count = new QSpinBox;
	spin_count->setMinimum(1);
	spin_count->setMaximum(2000000000);
	spin_count->setValue(5);

	btn_create = new QPushButton(tr("Create"));
	btn_cancel = new QPushButton(tr("Cansel"));

	box_h->addWidget(lbl_alg);
	box_h->addWidget(list_alg);
	box_h->addWidget(lbl_count);
	box_h->addWidget(spin_count);

	box_h_b->addWidget(btn_create);
	box_h_b->addStretch(1);
	box_h_b->addWidget(btn_cancel);

	box_v->addLayout(box_h);
	box_v->addLayout(box_h_b);
	setLayout(box_v);
}
