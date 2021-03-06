#include "..\\Deedee.Escpos\\Deedee.Escpos.h"

#pragma comment(lib, "..\\Debug\\Deedee.Escpos.lib")

#include <string>
#include <iostream>

int main(int, char)
{
	INT32 res;


	void* doc = 0;
	void* table = 0;
	DeedeeTableFormatterCreate(&table);
	DeedeeTableFormatterDefineColumn(table, 10);
	DeedeeTableFormatterDefineColumn(table, 15);
	DeedeeTableFormatterDefineColumn(table, 10);

	DeedeeTableFormatterAddColumnContent(table, 0, 0, L"1st");
	DeedeeTableFormatterAddColumnContent(table, 1, 0, L"2nd");
	DeedeeTableFormatterAddColumnContent(table, 2, 0, L"3st");
	DeedeeTableFormatterAddRow(table);

	DeedeeTableFormatterAddColumnContent(table, 0, 0, L"1stn");
	DeedeeTableFormatterAddColumnContent(table, 1, 0, L"2ndn");
	DeedeeTableFormatterAddColumnContent(table, 2, 0, L"3stn");
	DeedeeTableFormatterAddRow(table);

	DeedeeTableFormatterAddColumnContent(table, 0, 1, L"1st");
	DeedeeTableFormatterAddColumnContent(table, 1, 1, L"2nd");
	DeedeeTableFormatterAddColumnContent(table, 2, 1, L"3st");
	DeedeeTableFormatterAddRow(table);

	DeedeeTableFormatterAddColumnContent(table, 0, 2, L"1stn");
	DeedeeTableFormatterAddColumnContent(table, 1, 2, L"2ndn");
	DeedeeTableFormatterAddColumnContent(table, 2, 2, L"3stn");
	DeedeeTableFormatterAddRow(table);

	const wchar_t *str = 0;
	size_t size = 0;
	DeedeeTableFormatterGetBuffer(table, &str, &size);

	std::wstring testTable(str, str + size);
	std::wcout << testTable;

	res = DeedeeDocCreate(&doc);
	DeedeeDocReset(doc);
	//DeedeeDocSetFont(doc, 2);
	/*DeedeeDocSetPrinterCodePage(doc, 64);//737
	DeedeeDocSetCodePage(doc, 737);
	
	DeedeeDocWrite(doc, L"test left\n");
	DeedeeDocSetJustificationMode(doc,1);
	DeedeeDocWrite(doc,L"test at center\n");
	DeedeeDocSetJustificationMode(doc,2);
	DeedeeDocWrite(doc, L"test at right\n");
	DeedeeDocSetJustificationMode(doc,0);
	DeedeeDocSetEmphasized(doc, 1);
	DeedeeDocWrite(doc, L"test in bold\n");
	DeedeeDocSetEmphasized(doc, 0);
	DeedeeDocSetUnderlineMode(doc,1);
	DeedeeDocWrite(doc, L"test underline 1dot\n");
	DeedeeDocSetUnderlineMode(doc, 2);
	DeedeeDocWrite(doc, L"test underline 2dot\n");
	DeedeeDocSetUnderlineMode(doc, 0);
	DeedeeDocSetDoubleStrike(doc, 1);
	DeedeeDocWrite(doc, L"test doublestrike\n");
	DeedeeDocSetDoubleStrike(doc, 0);
	DeedeeDocWrite(doc, L"�������������� �� �� ��\n");
	DeedeeDocPrintMode(doc, 0, 1, 1, 1);
	DeedeeDocWrite(doc, L"big BIG\n");
	DeedeeDocPrintMode(doc, 0, 0, 0, 0);
	DeedeeDocWriteBarcode(doc, DEEDEEDOC_BARCODE_CODE39, L"12345678901");
	DeedeeDocFeed(doc);
	DeedeeDocWrite(doc, L"12345678901");
	DeedeeDocFeed(doc);
	auto qrText = L"Test test ���� ����";
	DeedeeDocCut(doc, 1);
	DeedeeDocSetCodePage(doc, 65001);//utf8
	//DeedeeDocWriteQR(doc, DEEDEEDOC_QR_MICRO, DEEDEEDOC_QR_CORR_L, qrText);
	DeedeeDocWriteQR1(doc,5, 3, qrText);
	DeedeeDocSetCodePage(doc,737);
	
	DeedeeDocWrite(doc,qrText);
	DeedeeDocFeed(doc);
	
	DeedeeDocCut(doc, 1);
	*/
	DeedeeDocSetJustificationMode(doc, 1);
	DeedeeDocWriteTableFormatter(doc,table);



	res = DeedeeDocFeed(doc);
	res = DeedeeDocCut(doc, 0);
	//res = DeedeeDocWrite(doc, L"test ������������t");
	//res = DeedeeDocFeedLines(doc, 3);
	//res = DeedeeDocCut(doc, 1);
	res = DeedeePrint(L"POS-80", doc);
	res = DeedeeDocDestroy(doc);
	return 0;
}
/*
protected function wrapperSend2dCodeData($fn, $cn, $data = '', $m = '')
{
if (strlen($m) > 1 || strlen($cn) != 1 || strlen($fn) != 1) {
throw new InvalidArgumentException("wrapperSend2dCodeData: cn and fn must be one character each.");
}
$header = $this -> intLowHigh(strlen($data) + strlen($m) + 2, 2);
$this -> connector -> write(self::GS . "(k" . $header . $cn . $fn . $m . $data);
}
*/