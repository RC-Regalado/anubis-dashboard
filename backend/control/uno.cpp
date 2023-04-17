#include <cppuhelper/bootstrap.hxx>
#include <com/sun/star/frame/XDesktop.hpp>

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::frame;

int main(int argc, char** argv)
{
    // Inicializar la API de LibreOffice
    Reference< XComponentContext > context = cppu::defaultBootstrap_InitialComponentContext();
    Reference< XMultiServiceFactory > serviceFactory = context->getServiceManager();
    Reference< XDesktop > desktop = Reference< XDesktop >(serviceFactory->createInstanceWithContext("com.sun.star.frame.Desktop", context), UNO_QUERY);

    // Guardar todos los archivos abiertos
    desktop->storeAll();

    return 0;
}

int save(int argc, char** argv)
{
    // Inicializar la biblioteca de UNO
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext > xContext = ::com::sun::star::uno::bootstrap();
    if (!xContext.is()) {
        std::cerr << "Error al inicializar la biblioteca de UNO" << std::endl;
        return EXIT_FAILURE;
    }

    // Obtener el servicio Desktop
    Reference<XDesktop> xDesktop(xContext->getServiceManager()->createInstanceWithContext("com.sun.star.frame.Desktop", xContext));

    // Guardar todos los documentos abiertos
    xDesktop->terminate();

    return EXIT_SUCCESS;
}



