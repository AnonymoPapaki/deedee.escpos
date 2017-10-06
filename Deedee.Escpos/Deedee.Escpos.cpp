#include "Deedee.Escpos.h"
#include "Deedee.EscposDocument.h"



INT32 DEEDEEAPI DeedeeDocCreate(void ** doc)
{
	void *tmp = new EscposDocument();
	if (!tmp)
		return -1;
	*doc = tmp;
	return 0;
}

INT32 DEEDEEAPI DeedeeDocDestroy(void * doc)
{
	delete (EscposDocument*)doc;
	return 0;
}

INT32 DEEDEEAPI DeedeeDocWrite(void * doc, const wchar_t * str)
{
	if (!doc || !str)
		return -1;
	try
	{
		((EscposDocument*)doc)->Write(str);
	}
	catch (std::exception &e)
	{
		return -1;
	}

	return 0;
}

INT32 DEEDEEAPI DeedeePrint(LPWSTR printerName, const void* doc)
{
	DOC_INFO_1 docInfo = {};
	docInfo.pDatatype = __TEXT("RAW");
	docInfo.pDocName = __TEXT("deedeedoc");

	const EscposDocument *d = (EscposDocument*)doc;
	INT32 error = 0;

	HANDLE hPrinter = NULL;
	if (!OpenPrinter(printerName, &hPrinter, NULL))
		return -1;
	if (StartDocPrinter(hPrinter, 1, (BYTE*)&docInfo))
	{
		if (StartPagePrinter(hPrinter))
		{
			DWORD dwWritten = 0;
			BOOL bSuccess = 
				WritePrinter(hPrinter, (LPVOID)d->GetBufferPointer(), d->GetBufferSize(), &dwWritten);
			EndPagePrinter(hPrinter);
			if (!bSuccess)
				error = -2;
			if (dwWritten != d->GetBufferSize())
				error = -3;
		}
		EndDocPrinter(hPrinter);
	}
	ClosePrinter(hPrinter);

	return error;
}
