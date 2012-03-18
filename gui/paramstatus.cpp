
#include "paramstatus.hpp"

#include <string>
#include <vector>

namespace pat
{

	ParamStatus::ParamStatus(QWidget * parent) : QWidget(parent)
	{
		lbl_points = new QLabel("0");
		lbl_result = new QLabel("0");
		lbl_iter = new QLabel("0");
		iter = 0;

		lay = new QGridLayout;
		lay->setSpacing(15);

		lay->addWidget(new QLabel(tr("Number of points in dimension") + ":"), 0, 0);
		lay->addWidget(lbl_points, 0, 1, Qt::AlignRight);

		lay->addWidget(new QLabel(tr("Result of the function") + ":"), 1, 0);
		lay->addWidget(lbl_result, 1, 1, Qt::AlignRight);

		lay->addWidget(new QLabel(tr("Number of iteration") + ":"), 2, 0);
		lay->addWidget(lbl_iter, 2, 1, Qt::AlignRight);


		table = new QTableWidget(1, 1);
		table->setColumnWidth(0, 250);
		table->setHorizontalHeaderLabels(QStringList(QString("value")));

		lay->addWidget(table, 3, 0, 1, 2);

		progress = new QProgressBar;
		progress->setMaximum(100);
		progress->setMinimum(0);
		progress->setValue(0);

		lay->addWidget(new QLabel(tr("Progress") + ":"), 4, 0);
		lay->addWidget(progress, 4, 1);

		setLayout(lay);
	}

	void ParamStatus::update(Status st)
	{
		Point p = st.minimum.point;
		table->setRowCount(p.dim());
		for (size_t i = 0; i < p.dim(); i++)
		{
			table->setItem(0, i, new QTableWidgetItem(QString::number(p[i].to_float())));
		}

		lbl_points->setText(QString::number(st.N));
		lbl_iter->setText(QString::number(st.iter));
		progress->setValue(static_cast<int>(100.0 * st.iter / static_cast<double>(st.N)));
		lbl_result->setText(QString::number(st.minimum.value.to_float()));
	}
}
