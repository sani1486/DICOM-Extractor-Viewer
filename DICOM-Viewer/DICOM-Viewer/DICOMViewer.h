#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qmessagebox.h>
#include "ui_DICOMViewer.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmdata/dcmetinf.h"
#include "dcmtk/dcmdata/dcvr.h"
#include "dcmtk/dcmdata/dctag.h"
#include "DcmWidgetElement.h"
#include "EditDialogSimple.h"

class DICOMViewer : public QMainWindow
{
	Q_OBJECT

	public:
		DICOMViewer(QWidget *parent = Q_NULLPTR);

	private:
		Ui::DICOMViewerClass ui;
		DcmFileFormat file;
		std::vector<DcmWidgetElement> elements;
		std::vector<DcmWidgetElement> nestedElements;
		int globalIndex = 0;
		int depthRE = 0;

	private:
		void insertInTable(DcmElement* element);
		void extractData(DcmFileFormat file);
		void repopulate(std::vector<DcmWidgetElement> source);
		void getNestedSequences(DcmTagKey tag);
		void iterateItem(DcmItem *item, int& depth);
		void clearTable();
		void alertFailed(std::string message);
		void indent(DcmWidgetElement& element, int depth);
		DcmWidgetElement createElement(
			DcmElement* element = nullptr, 
			DcmSequenceOfItems* sequence = nullptr, 
			DcmItem* item = nullptr);
		void insert(DcmWidgetElement element, int &index);
		double getFileSize(std::string fileName);

		void  getTagKeyOfSequence(DcmTagKey key, int row, DcmTagKey* returnKey, int* numberInSequence);

		bool deleteElementFromFile(DcmWidgetElement element, int row);
		bool canBeDeleted(DcmWidgetElement element);
		bool modifyValue(DcmWidgetElement element, int row, QString value);

		void createSimpleEditDialog(DcmWidgetElement element);
		void generatePathToRoot(DcmWidgetElement element, int row, QList<DcmWidgetElement> *elements);

	private slots:
		void fileTriggered(QAction* qaction);
		void closeButtonClicked();
		void editClicked();
		void deleteClicked();
		void insertClicked();
		void findText();
};
