
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

	void ParamStatus::update(Params params)
	{
		p = params;

		QStringList lst;
		QStringList lst_value;

		points_in_dims = 1;
		std::vector<std::string> list = p.get_list_params();
		if (p.dim() > 0)
		{
			for (int i = 0; i < p.dim(); i++)
			{
				points_in_dims *= p.get_points(list[i]);
				lst << QString(list[i].c_str());
				lst_value << QString(p.get_str(list[i]).c_str());
			}

			table->setRowCount(p.dim());
			table->setVerticalHeaderLabels(lst);

			for (int i = 0; i < p.dim(); i++)
			{
				table->setItem(0, i, new QTableWidgetItem(lst_value[i]));
			}

			iter++;
		}

		lbl_points->setText(QString::number(points_in_dims));
		lbl_iter->setText(QString::number(iter));
		progress->setValue(static_cast<int>(100.0 * iter / static_cast<double>(points_in_dims)));
		lbl_result->setText(QString::number(p.minvalue));
	}

}
