#define DEPURAR_HABILITADO 0
#if  !defined(DEPURAR_HABILITADO) || DEPURAR_HABILITADO==0
    #define DEBUG(a)
#else
    #define DEBUG(a) a
#endif

