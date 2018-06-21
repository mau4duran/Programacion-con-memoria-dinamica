#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef enum {false, true} Bool;

typedef enum {deposito=1, retiro, transferencia} tipoTransaccion;

typedef struct{
    int day, month, year;
}Fecha;

typedef struct{
    unsigned int id_usuario;
    char nombre[30];
    char apellido_materno[30];
    char apellido_paterno[30];
    Fecha fecha_nacimiento;
}Usuario;

char fCliente[120];
char fCuenta[120];
char fTransaccion[120];
void nuevoCliente(void);

typedef struct{
    unsigned int id_cuenta;
    unsigned int id_usuario;
    float saldo;
    Fecha fecha_apertura;
}Cuenta;

typedef struct{
    unsigned int id_transaccion;
    tipoTransaccion tipo_operacion;
    int cuenta_origen;
    int cuenta_destino;
    Fecha fecha_operacion;
    unsigned int monto;
}Transaccion;

char * init(void);
void validarCreacion(void);

void menuCliente(void);
void nuevoCliente(void);
Bool existeCliente(int index);
void consultarCliente(int index);
void eliminarCliente(int pos);
void imprimirClientes(void);

void menuCuenta(void);
void nuevaCuenta(void);
void buscarCuenta(int index);
void eliminarCuenta(int pos);
Bool existeCuenta(int index);
void eliminarCuentasUsuario(int pos);
void imprimirCuenta(void);

void menuTransaccion(void);
void nuevaTransaccion(tipoTransaccion tipo, int cuentaOrigen, int cuentaDestino, Fecha fecha, float monto);
Bool saldoSuficiente(int idCuenta, float monto);
void sumarSaldo(int id_cuenta, int monto);

void imprimirTransacciones(void);

int main() {
    int x = 0;
    char * w = init();
    char ClienteRoot[20]="Clientes.dat";
    char CuentaRoot[20]="Cuentas.dat";
    char TransaccionRoot[20]="Transacciones.dat";
    
    strcpy(fCliente, w);
    strcpy(fCuenta, w);
    strcpy(fTransaccion, w);
    strcat(fCliente, ClienteRoot);
    strcat(fCuenta, CuentaRoot);
    strcat(fTransaccion, TransaccionRoot);
    
    validarCreacion();

    while (x!=4) {
     printf("<< Sistema MyDB >>\n1.\tClientes\n2.\tCuentas\n3.\tTransacciones\n4.\tSalir\n");
     scanf("%d", &x);
        switch (x) {
            case 1:
                menuCliente();
                break;
            case 2:
                menuCuenta();
                break;
            case 3:
                menuTransaccion();
                break;
            case 4:
                break;
            default:
                printf("Input no es correcto\nVuelva a intentar.\n");
                break;
        }
        printf("Presione Enter para continuar");
        getchar();
        getchar();
        system("clear");
     }
    return 0;
}

char* init(){
    FILE * f = NULL;
    char root[200];
    f = fopen("mydb.sys", "r");
    
    if (f==NULL) {
        printf("Ruta de Acceso: ");
        scanf("%[^\n]", root);
        //gets(root);
        f = fopen("mydb.sys", "w");
        fputs(root, f);
        fclose(f);
    } else{
        fgets(root, 200, f);
    }
    fclose(f);
    return root;
}

void menuCuenta(){
    int condition = 0;
    int id = 0;
    printf("1.\tNueva Cuenta\n2.\tBuscar Cuenta\n3.\tEliminar Cuenta\n4.\tImprimir Cuentas\n");
    scanf("%d",&condition);
    switch (condition) {
        case 1:
            nuevaCuenta();
            break;
        case 2:
            printf("Escribar el id de Cuenta a buscar:");
            scanf("%d",&id);
            buscarCuenta(id);
            break;
        case 3:
            printf("Escribar el id de Cuenta a eliminar:");
            scanf("%d",&id);
            eliminarCuenta(id);
            break;
        case 4:
            imprimirCuenta();
            break;

        default:
            printf("Error. Opcion incorrecta.");
            break;
    }
}

void menuCliente(){
    int condition = 0;
    int id = 0;
    printf("1.\tNuevo Cliente\n2.\tBuscar Cliente\n3.\tEliminar Cliente\n4.\tImprimir\n");
    scanf("%d",&condition);
    switch (condition) {
        case 1:
            nuevoCliente();
            break;
        case 2:
            printf("Escribar el id de Cliente a buscar:");
            scanf("%d",&id);
            consultarCliente(id);
            break;
        case 3:
            printf("Escribar el id de Cliente a eliminar:");
            scanf("%d",&id);
            eliminarCliente(id);
            break;
        case 4:
            imprimirClientes();
            break;
            
        default:
            printf("Error. Opcion incorrecta.");
            break;
    }
}

void validarCreacion(){
    int z = 0;
    FILE * c = fopen(fCliente, "rb");
    FILE * d = fopen(fCuenta, "rb");
    FILE * e = fopen(fTransaccion, "rb");
    
    if (c==NULL) {
        c = fopen(fCliente, "wb");
        fwrite(&z, sizeof(int), 1, c);
    }
    
    if (d==NULL) {
        d = fopen(fCuenta, "wb");
        fwrite(&z, sizeof(int), 1, d);
    }
    
    if (e==NULL) {
        e = fopen(fTransaccion, "wb");
        fwrite(&z, sizeof(int), 1, e);
    }

    fclose(c);
    fclose(d);
    fclose(e);
}

/*************************
 
        Cliente
 
 *************************/

void nuevoCliente(){
    FILE * file;
    int cantidad;

    file = fopen(fCliente, "rb");
    fread(&cantidad, sizeof(int), 1, file);
    fclose(file);
    
    cantidad ++;
    file =  fopen(fCliente, "a+b");
    
    char nombre[30];
    char apellido_materno[30];
    char apellido_paterno[30];
    int dd, mm, yy;
    Usuario temp;
    
    temp.id_usuario = cantidad;
    
    printf("Nombre: ");
    scanf("%s", nombre);
    strcpy(temp.nombre, nombre);
    
    printf("Apellido Paterno: ");
    scanf("%s", apellido_paterno);
    strcpy(temp.apellido_paterno, apellido_paterno);
    
    printf("Apellido Materno: ");
    scanf("%s", apellido_materno);
    strcpy(temp.apellido_materno, apellido_materno);
    
    printf("Fecha de Nacimiento (dd/mm/yyyy) ");
    scanf("%d/%d/%d",&dd, &mm, &yy);
    
    temp.fecha_nacimiento.day = dd;
    temp.fecha_nacimiento.month = mm;
    temp.fecha_nacimiento.year = yy;
    
    fwrite(&temp, sizeof(Usuario), 1, file);
    fclose(file);
    file = fopen(fCliente, "r+b");
    fwrite(&cantidad, sizeof(int), 1, file);
    fclose(file);
    
}

Bool existeCliente(int index){
    int x=0, cond = 0;
    Usuario temp;
    FILE * file = fopen(fCliente, "rb");
    fread(&x, sizeof(int), 1, file);
    
    while (fread(&temp, sizeof(Usuario), 1, file)==1) {
        if (temp.id_usuario==index) {
            cond = 1;
            return true;
        }
    }
        return false;
    }


void consultarCliente(int index){
    int x=0, cond = 0;
    Usuario temp;
    FILE * file = fopen(fCliente, "rb");
    fread(&x, sizeof(int), 1, file);
    
    while (fread(&temp, sizeof(Usuario), 1, file)==1) {
        if (temp.id_usuario==index) {
            cond = 1;
            printf("%10s\t%-25s\t%-25s\t%-25s\t%-25s\n", "Id_Usuario","Nombre", "Apellido P.", "Apellido M", "Fecha" );
            
            printf("%-10d\t%-25s\t%-25s\t%-25s\t%02d/%02d/%04d\n", temp.id_usuario, temp.nombre, temp.apellido_paterno, temp.apellido_materno, temp.fecha_nacimiento.day, temp.fecha_nacimiento.month, temp.fecha_nacimiento.year);
        }
    }
    
    if (cond==0) {
        printf("Registro no encontrado\n");
    }
}

void eliminarCliente(int pos){
    int index;
    int condicion = 0;
    FILE * file;
    file = fopen(fCliente, "rb");
    fread(&index, sizeof(int), 1, file);
    int n = 1;
    Usuario * temp;

    int i = 0;
    Usuario * array = malloc(sizeof(Usuario) * n);
    
    while (fread(array+ i, sizeof(Usuario), 1, file)==1){
            temp = realloc(array, sizeof(Usuario)*(n+1));
        if (temp!=NULL) {
            array = temp;
        } else{
            printf("Error.");
        }
        i++;
        n++;
    }
    fclose(file);

    for (int i = 0; i<n-1; i++) {
        if (pos == array[i].id_usuario) {
            array[i].id_usuario = 0;
            condicion = 1;
        }
    }
    
    if (condicion==0) {
        
        return;
    }
    
    file = fopen(fCliente, "wb+");
    
    int indice;
    
    fwrite(&index, sizeof(int), 1, file);
    rewind(file);
    fread(&indice, sizeof(int), 1, file);
    
    for (int j = 0; j<n-1; j++) {
        if (array[j].id_usuario!=0) {
            fwrite(array+j, sizeof(Usuario), 1, file);
        }
    }
    //fseek(file, sizeof(int), SEEK_SET);
    
    fclose(file);
    free(array);
    
    eliminarCuentasUsuario(pos);
}

void imprimirClientes(){
    FILE * file = fopen(fCliente, "r+b");
    int x;
    fread(&x, sizeof(int), 1, file);
    Usuario temp;
    printf("%10s\t%-25s\t%-25s\t%-25s\t%-25s\n", "Id_Usuario","Nombre", "Apellido P.", "Apellido M", "Fecha" );
    while (fread(&temp, sizeof(Usuario), 1, file)==1) {
        printf("%-10d\t%-25s\t%-25s\t%-25s\t%02d/%02d/%04d\n", temp.id_usuario, temp.nombre, temp.apellido_paterno, temp.apellido_materno, temp.fecha_nacimiento.day, temp.fecha_nacimiento.month, temp.fecha_nacimiento.year);
    }
}

/*************************
        Cuenta
 *************************/

void nuevaCuenta(){
    FILE * file;
    int cantidad;
    
    file = fopen(fCuenta, "rb");
    fread(&cantidad, sizeof(int), 1, file);
    fclose(file);
    
    cantidad ++;
    file =  fopen(fCuenta, "a+b");
 
    int id_usuario;
    float saldo;
    int dd, mm, yy;
    Cuenta temp;
    
    temp.id_cuenta = cantidad;
 
    printf("Id Usuario: ");
    scanf("%d", &id_usuario);
    
    while(existeCliente(id_usuario)==false){
        printf("No se encontro id de usuario, vuelva a intentar.\n");
        scanf("%d", &id_usuario);
        
    }
    temp.id_usuario = id_usuario;
    
    printf("Saldo: ");
    scanf("%f", &saldo);
    temp.saldo = saldo;
    
    printf("Fecha de Apertura (dd/mm/yyyy) ");
    scanf("%d/%d/%d",&dd, &mm, &yy);
    
    temp.fecha_apertura.day = dd;
    temp.fecha_apertura.month = mm;
    temp.fecha_apertura.year = yy;
    
    fwrite(&temp, sizeof(Cuenta), 1, file);
    fclose(file);
    file = fopen(fCuenta, "r+b");
    fwrite(&cantidad, sizeof(int), 1, file);
    fclose(file);
}

void buscarCuenta(int index){
    int x=0, cond = 0;
    char nombre[30];
    char apellido_materno[30];
    char apellido_paterno[30];
    Cuenta temp;
    FILE * file = fopen(fCuenta, "rb");
    fread(&x, sizeof(int), 1, file);
    
    while (fread(&temp, sizeof(Cuenta), 1, file)==1) {
        if (temp.id_cuenta==index) {
            cond = 1;
            printf("%-10s\t%-15s%-15s%-15s\t%-15s\t%-15s\n", "Id_Cuenta","Nombre","Apellido P", "Apellido M", "Saldo.", "Fecha" );
            break;
        }
    }
    fclose(file);
    
    Usuario usrTemp;
    FILE * cliente = fopen(fCliente, "rb");
    if (cond==0) {
        printf("Registro no encontrado\n");
    }else{
        fseek(cliente, sizeof(int), SEEK_SET);
        
        while (fread(&usrTemp, sizeof(Usuario), 1, cliente)==1){

            if (temp.id_usuario==usrTemp.id_usuario) {
                strcpy(nombre, usrTemp.nombre);
                strcpy(apellido_paterno, usrTemp.apellido_paterno);
                strcpy(apellido_materno, usrTemp.apellido_materno);
                break;
            }
        }
        fclose(cliente);
        
       printf("%-10d\t%-15s %-15s %-15s\t%-13.2f\t%02d/%02d/%04d\n", temp.id_cuenta,nombre,apellido_paterno,apellido_materno,temp.saldo,temp.fecha_apertura.day,temp.fecha_apertura.month, temp.fecha_apertura.year);
    }
}

void eliminarCuentasUsuario(int pos){
    int index;
    int condicion = 0;
    FILE * file;
    file = fopen(fCuenta, "rb");
    fread(&index, sizeof(int), 1, file);
    int n = 1;
    Cuenta * temp;

    int i = 0;
    Cuenta * array = malloc(sizeof(Cuenta) * n);

    while (fread(array+ i, sizeof(Cuenta), 1, file)==1){
        temp = realloc(array, sizeof(Cuenta)*(n+1));
        if (temp!=NULL) {
            array = temp;
        } else{
            printf("Error.");
        }
        i++;
        n++;
    }
    fclose(file);

    for (int i = 0; i<n-1; i++) {
        if (pos == array[i].id_usuario) {
            array[i].id_cuenta = 0;
            condicion = 1;
        }
    }

    if (condicion==0) {
        printf("\n-Error. No se encontró cliente\n");
        return;
    }

    file = fopen(fCuenta, "wb+");

    int indice;

    fwrite(&index, sizeof(int), 1, file);
    rewind(file);
    fread(&indice, sizeof(int), 1, file);


    for (int j = 0; j<n-1; j++) {
        if (array[j].id_cuenta!=0) {
            fwrite(array+j, sizeof(Cuenta), 1, file);
        }
    }
    //fseek(file, sizeof(int), SEEK_SET);

    fclose(file);
    free(array);
}

void eliminarCuenta(int pos){
    int index;
    int condicion = 0;
    FILE * file;
    file = fopen(fCuenta, "rb");
    fread(&index, sizeof(int), 1, file);
    int n = 1;
    Cuenta * temp;
    
    int i = 0;
    Cuenta * array = malloc(sizeof(Cuenta) * n);
    
    while (fread(array+ i, sizeof(Cuenta), 1, file)==1){
        temp = realloc(array, sizeof(Cuenta)*(n+1));
        if (temp!=NULL) {
            array = temp;
        } else{
            printf("Error.");
        }
        i++;
        n++;
    }
    fclose(file);
    
    for (int i = 0; i<n-1; i++) {
        if (pos == array[i].id_cuenta) {
            array[i].id_cuenta = 0;
            condicion = 1;
        }
    }
    
    if (condicion==0) {
        printf("\n-Error. No se encontró cliente\n");
        return;
    }
    
    file = fopen(fCuenta, "wb+");
    
    int indice;
    
    fwrite(&index, sizeof(int), 1, file);
    rewind(file);
    fread(&indice, sizeof(int), 1, file);
    
    
    for (int j = 0; j<n-1; j++) {
        if (array[j].id_cuenta!=0) {
            fwrite(array+j, sizeof(Cuenta), 1, file);
        }
    }
    //fseek(file, sizeof(int), SEEK_SET);
    
    fclose(file);
    free(array);
}

void imprimirCuenta(){
    FILE * file = fopen(fCuenta, "r+b");
    int x;
    fread(&x, sizeof(int), 1, file);
    Cuenta temp;

    printf("%-10s\t%-15s%-15s%-15s\t%-15s\t%-15s\n", "Id_Cuenta","Nombre","Apellido P", "Apellido M", "Saldo.", "Fecha" );
    
    Usuario usrTemp;
    FILE * cliente = fopen(fCliente, "rb");
    
    while (fread(&temp, sizeof(Cuenta), 1, file)==1) {
        fseek(cliente, sizeof(int), SEEK_SET);
        
        while (fread(&usrTemp, sizeof(Usuario), 1, cliente)==1){
            
            if (temp.id_usuario==usrTemp.id_usuario) {

                printf("%-10d\t%-15s %-15s %-15s\t%-13.2f\t%02d/%02d/%04d\n", temp.id_cuenta,usrTemp.nombre,usrTemp.apellido_paterno,usrTemp.apellido_materno,temp.saldo,temp.fecha_apertura.day,temp.fecha_apertura.month, temp.fecha_apertura.year);
                break;
            }
        }
        
    }
}

Bool existeCuenta(int index){
    int x=0, cond = 0;
    Cuenta temp;
    FILE * file = fopen(fCuenta, "rb");
    fread(&x, sizeof(int), 1, file);

    while (fread(&temp, sizeof(Cuenta), 1, file)==1) {
        if (temp.id_cuenta==index) {
            cond = 1;
            return true;
        }
    }
    return false;
}

/*************************
        Transaccion
 *************************/

void menuTransaccion(){
    int condition = 0;
    int cuenta_origen;
    int cuenta_destino;
    float monto;
    Fecha date={0,0,0};
    printf("1.\tDeposito\n2.\tRetiro\n3.\tTransferencia\n4.\tImprimir\n");
    scanf("%d",&condition);
    if (condition!=4) {
        printf("Escriba la fecha de la operacion dd/mm/yyyy: ");
        scanf("%d/%d/%d",&date.day, &date.month, &date.year);
    }

    switch (condition) {
        case 1:
            printf("Inserte el monto a depositar: ");
            scanf("%f", &monto);
            printf("Inserte el id de la cuenta destino: ");
            scanf("%d",&cuenta_destino);
            nuevaTransaccion(deposito, 0, cuenta_destino, date, monto);
            break;
        case 2:
            printf("Inserte el monto a retirar: ");
            scanf("%f", &monto);
            printf("Inserte el id de la cuenta origen: ");
            scanf("%d",&cuenta_origen);
            nuevaTransaccion(retiro, cuenta_origen, 0, date, monto);
            break;
            
        case 3:
            printf("Inserte el monto a transferir: ");
            scanf("%f", &monto);
            printf("Inserte el id de la cuenta origen: ");
            scanf("%d",&cuenta_origen);
            printf("Inserte el id de la cuenta destino: ");
            scanf("%d",&cuenta_destino);
            nuevaTransaccion(transferencia, cuenta_origen, cuenta_destino, date, monto);
            break;
        case 4:
            imprimirTransacciones();
            break;
            
        default:
            printf("Error. Opcion incorrecta.");
            break;
    }
}

void nuevaTransaccion(tipoTransaccion tipo, int cuentaOrigen, int cuentaDestino, Fecha fecha, float monto){
    FILE * file;
    int cantidad;
    file = fopen(fTransaccion, "rb");
    fread(&cantidad, sizeof(int), 1, file);
    fclose(file);
    cantidad ++;
    file =  fopen(fTransaccion, "a+b");
  
    Transaccion temp;
    
    temp.id_transaccion = cantidad;
    temp.cuenta_destino = cuentaDestino;
    temp.cuenta_origen = cuentaOrigen;
    temp.tipo_operacion = tipo;
    temp.monto = monto;
    temp.fecha_operacion.day = fecha.day;
    temp.fecha_operacion.month = fecha.month;
    temp.fecha_operacion.year = fecha.year;
    
    switch (tipo) {
        case deposito:
            while (!existeCuenta(temp.cuenta_destino)) {
                printf("Id de cuenta destino no encontrado. Vuelva a intentar.\n");
                scanf("%d",&temp.cuenta_destino);
            }
            sumarSaldo(temp.cuenta_destino, temp.monto);
            break;
            
        case retiro:
            while (!existeCuenta(temp.cuenta_origen)) {
                printf("Id de cuenta origen no encontrado. Vuelva a intentar.\n");
                scanf("%d",&temp.cuenta_origen);
            }
            while(!saldoSuficiente(temp.cuenta_origen, temp.monto)){
                printf("No se cuenta con el saldo suficiente. Vuelva a intentar.\n");
                scanf("%d",&temp.monto);
                
            }
            sumarSaldo(temp.cuenta_origen, -1*temp.monto);
            break;
            
        case transferencia:
            while (!existeCuenta(temp.cuenta_destino)) {
                printf("Id de cuenta destino no encontrado. Vuelva a intentar.\n");
                scanf("%d",&temp.cuenta_destino);
            }
            while (!existeCuenta(temp.cuenta_origen)) {
                printf("Id de cuenta origen no encontrado. Vuelva a intentar.\n");
                scanf("%d",&temp.cuenta_origen);
            }
            
            while(!saldoSuficiente(temp.cuenta_origen, temp.monto)){
                printf("No se cuenta con el saldo suficiente. Vuelva a intentar.\n");
                scanf("%d",&temp.monto);
            }
            sumarSaldo(temp.cuenta_origen, -1*temp.monto);
            sumarSaldo(temp.cuenta_destino, temp.monto);
            break;
            
        default:
            printf("Error.\n");
            break;
    }
    
    fwrite(&temp, sizeof(Transaccion), 1, file);
    fclose(file);
    file = fopen(fTransaccion, "r+b");
    fwrite(&cantidad, sizeof(int), 1, file);
    fclose(file);
    
}

Bool saldoSuficiente(int idCuenta, float monto){
    FILE * file;
    file = fopen(fCuenta, "rb");
    Cuenta temp;
    fseek(file, sizeof(int), SEEK_SET);
    while (fread(&temp, sizeof(Cuenta), 1, file)==1) {
        if (temp.id_cuenta==idCuenta) {
            if (temp.saldo>=monto) {
                return true;
            }
            
        }
    }
    return false;
}

void imprimirTransacciones(){
    FILE * file = fopen(fTransaccion, "r+b");
    int x;
    char * type[]={"Deposito","Retiro", "Transferencia"};
    fread(&x, sizeof(int), 1, file);
    Transaccion temp;
    printf("%15s\t%-20s\t%-20s\t%-20s\t%-15s\t%-15s\n", "Id_Transaccion","Tipo Transaccion", "Id Cuenta_Origen", "Id Cuenta_Destino", "Fecha", "Monto");
    while (fread(&temp, sizeof(Transaccion), 1, file)==1) {
        printf("%-15d\t%-20s\t%-20d\t%-20d\t%02d/%02d/%04d\t%-15d\n",temp.id_transaccion, type[temp.tipo_operacion-1],temp.cuenta_origen,temp.cuenta_destino, temp.fecha_operacion.day,temp.fecha_operacion.month, temp.fecha_operacion.year, temp.monto) ;
    }
}

void sumarSaldo(int id_cuenta, int monto){
    FILE * archivo;
    archivo = fopen(fCuenta, "r+b");
    
    Cuenta temporal;
    fseek(archivo, sizeof(int), 1);
    while (fread(&temporal, sizeof(Cuenta), 1, archivo)==1){
        if (temporal.id_cuenta==id_cuenta) {
            temporal.saldo += monto;
            fseek(archivo, -sizeof(Cuenta), SEEK_CUR);
            fwrite(&temporal, sizeof(Cuenta), 1, archivo);
        }
    }
}
