#include <addon.hxx>

#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include <com/sun/star/container/XEnumerationAccess.hpp>
#include <com/sun/star/container/XContentEnumerationAccess.hpp>
#include <com/sun/star/container/XEnumeration.hpp>
#include <com/sun/star/container/XNameAccess.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>

#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XSingleServiceFactory.hpp>

#include <com/sun/star/bridge/XUnoUrlResolver.hpp>

#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/frame/XFrame.hpp>
#include <com/sun/star/frame/XController.hpp>
#include <com/sun/star/frame/XModel.hpp>

#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/uno/XInterface.hpp>

#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XText.hpp>
#include <com/sun/star/text/XTextRange.hpp>
#include <com/sun/star/text/XTextRangeCompare.hpp>
#include <com/sun/star/text/XTextTable.hpp>
#include <com/sun/star/text/XTextTableCursor.hpp>
#include <com/sun/star/text/XTextTablesSupplier.hpp>

#include <com/sun/star/view/XSelectionSupplier.hpp>

#include <com/sun/star/beans/XPropertySet.hpp>

#include <com/sun/star/table/XCell.hpp>
#include <com/sun/star/table/TableBorder.hpp>
#include <com/sun/star/table/XTableRows.hpp>

#include <cppuhelper/supportsservice.hxx>
#include <cppuhelper/bootstrap.hxx>

#include <rtl/ustring.hxx>

using rtl::OUString;
using namespace cppu;
using namespace com::sun::star::uno;
using namespace com::sun::star::frame;
using namespace com::sun::star::table;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::text;
using namespace com::sun::star::view;
using namespace com::sun::star::bridge;
using namespace com::sun::star::container;
using com::sun::star::util::URL;

#define SERVICE_NAME "com.sun.star.frame.ProtocolHandler"

void TransposeTable(Reference<XTextTable>& xTable) {
    Reference<XTextTableCursor> cur = xTable->createCursorByCellName(OUString::createFromAscii("A1"));

    size_t columns = 1;
    size_t row = 1;

    while (cur->goDown(1, false)) {
        columns++;
    }
    while (cur->goRight(1, false)) {
        row++;
    }

    size_t n = std::min(row, columns);
    for (size_t y = 0; y < n; y++) {
        for (size_t x = y; x < n; x++) {
            std::string xCoord_1;
            xCoord_1 += (char) ('A' + x);
            xCoord_1 += std::to_string(y + 1);

            std::string xCoord_2;
            xCoord_2 += (char) ('A' + y);
            xCoord_2 += std::to_string(x + 1);

            Reference<XCell> xCell_1 = xTable->getCellByName(OUString::createFromAscii(xCoord_1.c_str()));
            Reference<XCell> xCell_2 = xTable->getCellByName(OUString::createFromAscii(xCoord_2.c_str()));
            Reference<XText> xTextCell_1(xCell_1, UNO_QUERY);
            Reference<XText> xTextCell_2(xCell_2, UNO_QUERY);
            OUString tmp = xTextCell_1->getString();
            xTextCell_1->setString(xTextCell_2->getString());
            xTextCell_2->setString(tmp);
        }
    }
}

void TransposeAllDocument(Reference<XFrame>& rxFrame) {
    Reference<XTextDocument> xTextDocument(rxFrame->getController()->getModel(), UNO_QUERY);

    Reference<XTextTablesSupplier> xTables(xTextDocument, UNO_QUERY);
    Reference<XNameAccess> arTables = xTables->getTextTables();

    auto tables = arTables->getElementNames();
    for (auto& i : tables) {
        auto tmp = arTables->getByName(i);
        Reference<XTextTable> xTable;
        tmp >>= xTable;

        TransposeTable(xTable);
    }
}

void CreateNewTable(Reference<XFrame> &rxFrame, Reference<XComponentContext>& rxContext) {
    Reference<XComponentLoader> rComponentLoader(rxFrame, UNO_QUERY);

    Reference<XComponent> xWriterComponent = rComponentLoader->loadComponentFromURL(
        OUString::createFromAscii("private:factory/swriter"),
        OUString::createFromAscii("_default"),
        0,
        Sequence<PropertyValue>());

    Reference<XTextDocument> xTextDocument (xWriterComponent, UNO_QUERY);

    Reference<XText> xText = xTextDocument->getText();
    Reference<XTextCursor> xTextCursor = xText->createTextCursor();

    std::srand(std::time(NULL));
    size_t countTable = std::rand() % 7 + 2;
    for (size_t i = 0; i < countTable; i++) {
        xTextCursor->gotoEnd(false);
        std::string s = std::string("\n").append(std::to_string(i + 1));
        s.append("\n");
        xTextCursor->setString(OUString::createFromAscii(s.c_str()));

        Reference<XMultiServiceFactory> oDocMSF(xTextDocument, UNO_QUERY);
        Reference<XTextTable> xTable(oDocMSF->createInstance(OUString::createFromAscii("com.sun.star.text.TextTable")), UNO_QUERY);

        size_t rows = 3 + std::rand() % 8;
        size_t columns = 3 + std::rand() % 4;
        xTable->initialize(rows, columns);
        Reference<XTextContent> xTextContent(xTable, UNO_QUERY);
        // Any prop;
        // Reference<XTableRows> xTableRows = xTable->getRows();
        // Reference<XIndexAccess> theRows (xTableRows,UNO_QUERY);
        // Reference<XPropertySet> xRowProps (theRows->getByIndex((short)0),UNO_QUERY);
        // prop <<= (sal_Bool)false;
        // xRowProps->setPropertyValue(OUString::createFromAscii("BackTransparent"),prop);

        xText->insertTextContent(xText->getEnd(), xTextContent, (unsigned char) 0);
        for (size_t y = 0; y < rows; y++) {
            for (size_t x = 0; x < columns; x++) {
                std::string index;
                index += (char) ('A' + x);
                index += std::to_string(y + 1);

                std::string val = std::string("(") + std::to_string(y+1) + std::string(", ") + std::to_string(x+1) + std::string(")");

                Reference<XCell> xCell = xTable->getCellByName(OUString::createFromAscii(index.c_str()));
                Reference<XText> xTextCell(xCell, UNO_QUERY);
                Reference<XTextCursor> xTextCursor2 = xTextCell->createTextCursor();

                xTextCursor2->setString(OUString::createFromAscii(val.c_str()));
            }
        }
    }
}

// XDispatch implementer class "DateTimeWriterDispatchImpl" methods
void SAL_CALL AddonDispatchImpl::dispatch(const URL& aURL, const Sequence <PropertyValue>& lArgs) throw (RuntimeException) {
    if (aURL.Protocol.equalsAscii("inco.niocs.test.protocolhandler:")) {
        if (aURL.Path.equalsAscii("Transpose")) {
            TransposeAllDocument(mxFrame);
        } else if (aURL.Path.equalsAscii("Insert")) {
            CreateNewTable(mxFrame, mxContext);
        }
    }
}

void SAL_CALL AddonDispatchImpl::addStatusListener(const Reference<XStatusListener>& xControl, const URL& aURL) throw (RuntimeException) {
}

void SAL_CALL AddonDispatchImpl::removeStatusListener(const Reference<XStatusListener>& xControl, const URL& aURL) throw (RuntimeException) {
}

// ProtocolHandler implementation "Addon" class methods

void SAL_CALL Addon::initialize(const Sequence<Any>& aArguments) throw (Exception, RuntimeException) {
    Reference<XFrame> xFrame;
    if (aArguments.getLength()) {
        aArguments[0] >>= xFrame;
        mxFrame = xFrame;
    }
}

Reference<XDispatch> SAL_CALL Addon::queryDispatch(const URL& aURL, const ::rtl::OUString& sTargetFrameName, sal_Int32 nSearchFlags) throw (RuntimeException) {
    Reference<XDispatch> xRet;
    if (aURL.Protocol.equalsAscii("inco.niocs.test.protocolhandler:")) {
        if (aURL.Path.equalsAscii("Transpose")) {
            xRet = new AddonDispatchImpl(mxFrame, mxContext);
        } else if (aURL.Path.equalsAscii("Insert")) {
            xRet = new AddonDispatchImpl(mxFrame, mxContext);
        }
    }

    return xRet;
}


Sequence<Reference<XDispatch>> SAL_CALL Addon::queryDispatches(const Sequence<DispatchDescriptor>& seqDescripts) throw (RuntimeException) {
    sal_Int32 nCount = seqDescripts.getLength();
    Sequence<Reference<XDispatch>> lDispatcher(nCount);

    for (sal_Int32 i = 0; i < nCount; ++i)
        lDispatcher[i] = queryDispatch(seqDescripts[i].FeatureURL, seqDescripts[i].FrameName, seqDescripts[i].SearchFlags);

    return lDispatcher;
}


// Helper functions for the implementation of UNO component interfaces.
OUString Addon_getImplementationName() throw (RuntimeException) {
    return OUString(IMPLEMENTATION_NAME);
}

Sequence<::rtl::OUString> SAL_CALL Addon_getSupportedServiceNames() throw (RuntimeException) {
    Sequence <::rtl::OUString> aRet(1);
    ::rtl::OUString* pArray = aRet.getArray();
    pArray[0] = OUString(SERVICE_NAME);
    return aRet;
}

Reference<XInterface> SAL_CALL Addon_createInstance(const Reference<XComponentContext> & rContext) throw (Exception) {
    return (cppu::OWeakObject*) new Addon(rContext);
}

// Implementation of the recommended/mandatory interfaces of a UNO component.
// XServiceInfo
::rtl::OUString SAL_CALL Addon::getImplementationName() throw (RuntimeException) {
    return Addon_getImplementationName();
}

sal_Bool SAL_CALL Addon::supportsService(const ::rtl::OUString& rServiceName) throw (RuntimeException) {
    return cppu::supportsService(this, rServiceName);
}

Sequence<::rtl::OUString> SAL_CALL Addon::getSupportedServiceNames() throw (RuntimeException) {
    return Addon_getSupportedServiceNames();
}
