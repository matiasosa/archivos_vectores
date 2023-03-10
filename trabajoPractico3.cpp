#include <iostream>
using namespace std;

const int CANT_CAUSAS = 11;
const int CANT_PERICIAS = 9;
const int CANT_RELCP = 8;

struct Causas{
    int id_causa;
    int fecha_ingreso;
    int id_origen;
    char origen[51];
};

struct Pericias{
    int id_pericias;
    int id_tipopericia;
    int fecha;
    char tipopericia[101];
};

struct RCausasPericias
{
    int id_causa;
    int id_pericia;
};

struct MesOrigen
{
    int mes;
    string origen;
    int cont;
};

struct PericiaOrigen
{
    string tipopericia;
    string origen;
    int cont;
};

// PUNTO 1

void cargarDatosCausas(FILE* f)
{
    Causas causa;

    causa = (struct Causas) {9945, 20220615, 2, "Denuncia PJN"};
    fwrite(&causa, sizeof(Causas), 1, f);

    causa = (struct Causas) {8954, 20220219, 3, "Denuncia MPF"};
    fwrite(&causa, sizeof(Causas), 1, f);

    causa = (struct Causas) {9015, 20220310, 1, "Prevencion de FFSS"};
    fwrite(&causa, sizeof(Causas), 1, f);

    causa = (struct Causas) {9055, 20220415, 4, "Denuncia FFSS"};
    fwrite(&causa, sizeof(Causas), 1, f);

    causa = (struct Causas) {9110, 20220508, 1, "Prevencion de FFSS"};
    fwrite(&causa, sizeof(Causas), 1, f);

    causa = (struct Causas) {9120, 20220517, 5, "Cooperacion Internacional"};
    fwrite(&causa, sizeof(Causas), 1, f);

    causa = (struct Causas) {9133, 20220522, 3, "Denuncia MPF"};
    fwrite(&causa, sizeof(Causas), 1, f);

    causa = (struct Causas) {9201, 20220605, 3, "Denuncia MPF"};
    fwrite(&causa, sizeof(Causas), 1, f);

    causa = (struct Causas) {9102, 20220621, 2, "Denuncia PJN"};
    fwrite(&causa, sizeof(Causas), 1, f);

    causa = (struct Causas) {8944, 20220209, 3, "Denuncia MPF"};
    fwrite(&causa, sizeof(Causas), 1, f);

    causa = (struct Causas) {9128, 20220318, 5, "Coopercacion  Internacional"};
    fwrite(&causa, sizeof(Causas), 1, f);
}

void cargarDatosPericias(FILE* p)
{
    Pericias pericia;

    pericia = (struct Pericias) {15985, 2, 20220215,"Copia Forense HD"};
    fwrite(&pericia, sizeof(Pericias), 1, p);
    
    pericia = (struct Pericias){15991, 4, 20220215,"Extraccion de datos dispositivo móvil"};
    fwrite(&pericia, sizeof(Pericias), 1, p);
    
    pericia = (struct Pericias){14120, 1, 20220119,"Extracción de datos laptop"};
    fwrite(&pericia, sizeof(Pericias), 1, p);
    
    pericia = (struct Pericias) {18302, 2, 20220815,"Copia Forense HD"};
    fwrite(&pericia, sizeof(Pericias), 1, p);

    pericia = (struct Pericias) {17535, 1, 20220622,"Extracción de datos laptop"};
    fwrite(&pericia, sizeof(Pericias), 1, p);
    
    pericia = (struct Pericias) {14018, 4, 20220105,"Extracción de datos dispositivo móvil"};
    fwrite(&pericia, sizeof(Pericias), 1, p);

    pericia = (struct Pericias) {16009, 5, 20220218,"Análisis historial navegacion"};
    fwrite(&pericia, sizeof(Pericias), 1, p);
    
    pericia = (struct Pericias) {17520, 4, 20220613,"Extracción de datos dispositivo móvil"};
    fwrite(&pericia, sizeof(Pericias), 1, p);
    
    pericia = (struct Pericias) {16110, 5, 20220222,"Análisis historial navegacion"};
    fwrite(&pericia, sizeof(Pericias), 1, p);
}

void cargarDatosRCausasPericias(FILE* r)
{
    RCausasPericias relCP;

    relCP = (struct RCausasPericias){9945, 15985};
    fwrite(&relCP, sizeof(RCausasPericias), 1, r);
    
    relCP = (struct RCausasPericias){9945, 15991}; 
    fwrite(&relCP, sizeof(RCausasPericias), 1, r);

    relCP = (struct RCausasPericias){8954, 18302};
    fwrite(&relCP, sizeof(RCausasPericias), 1, r);

    relCP = (struct RCausasPericias){8954, 17535};
    fwrite(&relCP, sizeof(RCausasPericias), 1, r);

    relCP = (struct RCausasPericias){9015, 16009};
    fwrite(&relCP, sizeof(RCausasPericias), 1, r);

    relCP = (struct RCausasPericias){9015, 17520};
    fwrite(&relCP, sizeof(RCausasPericias), 1, r);

    relCP = (struct RCausasPericias){9055, 16110};
    fwrite(&relCP, sizeof(RCausasPericias), 1, r);

    relCP = (struct RCausasPericias){9110, 14120};
    fwrite(&relCP, sizeof(RCausasPericias), 1, r);
}

// PUNTO 2

void ordenarArray(Causas arrayCausas[])
{
    for (int i = 1; i < CANT_CAUSAS; i++)
    {
        for (int j = 1; j <= CANT_CAUSAS - i; j++)
        {
            int fecha1 = arrayCausas[j-1].fecha_ingreso / 100;
            int fecha2 = arrayCausas[j].fecha_ingreso / 100;
            Causas aux;

            if (fecha1 > fecha2)
            {
                aux = arrayCausas[j-1];
                arrayCausas[j-1] = arrayCausas[j];
                arrayCausas[j] = aux;
            }
        }
    }
}

int estaEnArrayMesOrigen(MesOrigen arrayMesOrigen[], int mes, string origen){
    for (int i = 0; i < CANT_CAUSAS; i++)
    {
        if (arrayMesOrigen[i].mes == mes)
        {
            if (arrayMesOrigen[i].origen == origen)
            {
                return i;
            }
        }
    }
    return -1;
}

void mostrarCausas(Causas arrayCausas[])
{
    MesOrigen arrayMesOrigen[CANT_CAUSAS];
    int n = 0;
    for (int i = 0; i < CANT_CAUSAS; i++)
    {
        int mes = arrayCausas[i].fecha_ingreso / 100;
        string origen = arrayCausas[i].origen;

        int pos = estaEnArrayMesOrigen(arrayMesOrigen, mes, origen);

        if (pos != -1)
        {
            arrayMesOrigen[pos].cont++;
        }
        else
        {
            MesOrigen m = {mes, origen, 1};
            arrayMesOrigen[n] = m;
            n++;
        }      
    }

    for (int i = 0; i < n; i++)
    {
        cout << "Año y mes: " << arrayMesOrigen[i].mes << "     Origen: " << arrayMesOrigen[i].origen << endl;
        cout << "Cantidad de causas ingresadas: " << arrayMesOrigen[i].cont << endl;
        cout << "_____________________________________" << endl << endl;
    }
    
}

void reporteCausas(FILE* f, Causas arrayCausas[])
{
    int i = 0;
    Causas c;

    fseek(f, 0, SEEK_SET);
    fread(&c, sizeof(Causas), 1, f);
    while (!feof(f))
    {
        arrayCausas[i] = c;
        fread(&c, sizeof(Causas), 1, f);
        i++;
    }

    ordenarArray(arrayCausas);

    mostrarCausas(arrayCausas);
}

// PUNTO 3

string obtenerOrigen(Causas arrayCausas[], int idCausa)
{
    string ret;
    for (int i = 0; i < CANT_CAUSAS; i++)
    {
        if (idCausa == arrayCausas[i].id_causa)
        {
            ret = arrayCausas[i].origen;
        }
    }
    return ret;   
}

string obtenerTipoPericia(Pericias arrayPericias[], int idPericia)
{
    string ret;
    for (int i = 0; i < CANT_CAUSAS; i++)
    {
        if (idPericia == arrayPericias[i].id_pericias)
        {
            ret = arrayPericias[i].tipopericia;
        }
    }
    return ret;   
}

int estaEnArrayOP(PericiaOrigen arrayOP[], string origen, string tPericia)
{
    for (int i = 0; i < CANT_RELCP; i++)
    {
        if (tPericia == arrayOP[i].tipopericia)
        {
            if (origen == arrayOP[i].origen)
            {
                return i;
            }
        }
    }
    return -1;
}

void mostrarOrigenPericia(PericiaOrigen arrayOP[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Tipo pericia: " << arrayOP[i].tipopericia << " Origen: " << arrayOP[i].origen << endl;
        cout << "Cantidad de causas ingresadas: " << arrayOP[i].cont << endl;
        cout << "_____________________________________" << endl << endl;
    }
}

void reportePericias(FILE* p, FILE* r, Causas arrayCausas[])
{   
    int i = 0;
    Pericias k;
    Pericias arrayPericias[CANT_PERICIAS];
    fseek(p, 0, SEEK_SET);
    fread(&k, sizeof(Pericias), 1, p);
    while (!feof(p))
    {
        arrayPericias[i] = k;
        fread(&k, sizeof(Pericias), 1, p);
        i++;
    }

    PericiaOrigen arrayOP[CANT_RELCP];

    int j = 0, n = 0;
    RCausasPericias m;
    fseek(r, 0, SEEK_SET);
    fread(&m, sizeof(RCausasPericias), 1, r);
    while (!feof(r))
    {
        string origen = obtenerOrigen(arrayCausas, m.id_causa);
        string tPericia = obtenerTipoPericia(arrayPericias, m.id_pericia);

        int pos = estaEnArrayOP(arrayOP, origen, tPericia);
        if (pos != -1)
        {
            arrayOP[pos].cont++;
        }
        else
        {
            PericiaOrigen x = {origen, tPericia, 1};
            arrayOP[n] = x;
            n++;
        }
        
        fread(&m, sizeof(RCausasPericias), 1, r);
        j++;
    }

    mostrarOrigenPericia(arrayOP, n);
}

int main(){

    // PUNTO 1

    FILE* f = fopen("CAUSAS.DAT", "w+b");
    cargarDatosCausas(f); 

    FILE* p = fopen("PERICIAS_INFORMATICAS.DAT", "w+b");
    cargarDatosPericias(p);

    FILE* r = fopen("REL_CAUSA_PERICIA.DAT", "w+b");
    cargarDatosRCausasPericias(r);

    // PUNTO 2

    cout << endl << "PUNTO 2: " << endl << endl;
    Causas arrayCausas[CANT_CAUSAS];
    reporteCausas(f, arrayCausas);

    // PUNTO 3

    cout << endl << "PUNTO 3: " << endl << endl;
    reportePericias(p, r, arrayCausas);

    fclose(f);
    fclose(p);
    fclose(r);

    return 0;
}
