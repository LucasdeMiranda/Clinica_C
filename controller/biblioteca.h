#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif
typedef struct
{
    long int codigo;
    long int qnt; // quantidade usada daquele material
} Codmedicamentosmateriais;

typedef struct
{
    long int codigo;
    char descricao[1000];
    float precocustounid, total;
    long int qnt;        // quantidade recebida
} Codmateriaisrecebidos; // vai ser o reponsavel por armazenar as informações da nota fiscal do estoque

typedef struct
{
    char rua[200];
    char bairro[200];
    char cidade[200];
    char estado[10]; // Ex: "SP"
    long int numero;
} Endereco;

typedef struct
{
    long int codigo;
    char nomeCompleto[200];
    char cpf[50];
    Endereco endereco;
    char telefone[20];
    char dataNascimento[40];
    char historicoMedico[2000];
} Paciente;

typedef struct
{
    long int codigo;
    char nomeCompleto[200];
    char crm[50];
    char especialidade[400];
    char cpf[50];
    char telefone[20];
    char email[300];
} Profissional;

typedef struct
{
    long int codigo;
    char nomeFantasia[100];
    char razaoSocial[200];
    char inscricaoEstadual[200];
    char cnpj[40];
    Endereco endereco;
    char telefone[20];
    char email[300];
} Fornecedor;

typedef struct
{
    long int codigo;
    char descricaoProcedimento[1000];
} AmbienteMedico;

typedef struct
{
    long int codigo;
    char descricao[1000];
    char fabricante[300];
    long int codfornecedor; // codigo do fornecedor
    float precoCusto;
    float precoVenda;
    long int quantidadeEstoque;
    long int estoqueMinimo;
} MedicamentoMaterial;

typedef struct
{
    long int codigo;
    char descricao[2000];
    float custo;
    long int tempoEstimado;
    Codmedicamentosmateriais *codmedicamentosemateriais;
    long int codambientemedico; // codigo do ambiente medico
    long int tamcodmedicamentosmateriais;
} Procedimento;

typedef struct
{
    long int codigo, codpaciente, codprofissional, codprocedimento;
    char data[20], horario[20], horariofim[20];
} Agendamento;

typedef struct
{
    long int codigo;
    char cnpj[1000], fornecedor[1000];
    char data[1000];
    float frete, imposto, totaldetudo;
    Codmateriaisrecebidos *codmedicamentosmateriaisrecebidos;
    long int codfornecedor;
    long int tammedicamentosmateriaisrecebidos;
} Entradaestoque;

typedef struct
{
    char data[100];
    int tipo; // 0 para lançamento a vista 1 para retirada 2 para a receber
    float valor;
    long int codigoagendamento;    // para os a vista
    long int codigoentradaestoque; // registtra  o codigo da entrada do estoque vai ser ultil para relatorios
} LacamentosRetiradas;

typedef struct
{
    long int codigoagendamento; // para os que são para frente
    long int codigo;
    float valor;
    char data[100];
} Receber;

// menus auxiliares memoria
void menuambientesmedicos(AmbienteMedico **ambientes, long int *tamambiente, long int *codigoatual);
void menufornecedores(Fornecedor **fornecedores, long int *tamfornecedor, long int *codigoatatual);
void menumedicamentos_materiais(MedicamentoMaterial **medicamentosmateriais, long int *tammedicamentomaterial, long int *codigoatual);
void menupacientes(Paciente **pacientes, long int *tampacientes, long int *codigoatual);
void menuprocedimentos(Procedimento **procedimentos, long int *tamprocedimento, long int *codigoatual, AmbienteMedico *ambientes, MedicamentoMaterial *medicamentosmateriais,
                       long int tamambientes, long int tammedicamentomaterial);
void menuprofisionais(Profissional **profissionais, long int *tamprofissionais, long int *codigoatual);
void menuagendamento_controle(Agendamento **agendamentos, long int *tamagendamento, long int *codigoatual, Procedimento *procedimentos,
                              long int tamprocedimento, MedicamentoMaterial **medicamentosmateriais,
                              long int tammedicamentomaterial, Paciente *pacientes, long int tampacientes,
                              Profissional *profissionais, long int tamprofissionais);
void menuestoque(Entradaestoque **entradaestoque, MedicamentoMaterial **medicamentosmateriais,
                 long int tammedicamentomaterial, long int *tamentradaestoque, long int *codigoatual);

void menucaixa(float *saldototal, LacamentosRetiradas **lancamentosretiradas, Receber **receber,
               long int *tamlancamentosretiradas, long int *tamreceber, long int *codigoatualreceber,
               Agendamento *agendamentos, long int tamagendamento, Procedimento *procedimentos,
               long int tamprocedimento, Entradaestoque *entradaestoque, long int tamentradaestoque);
// cadastros
AmbienteMedico *cadastrarambientemedico(AmbienteMedico *ambientes, long int *tamambiente, long int *codigoatual, AmbienteMedico *novoambiente);
Fornecedor *cadastrarfornecedor(Fornecedor *fornecedores, long int *tamfornecedor, long int *codigoatual, Fornecedor *novofornecedor);
MedicamentoMaterial *cadastrarmedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int *tammedicamentomaterial, long int *codigoatual, MedicamentoMaterial *novomedicamentomaterial);
Paciente *cadastrarpaciente(Paciente *pacientes, long int *tampacientes, long int *codigoatual, Paciente *novopaciente);
Procedimento *cadastrarprocedimento(Procedimento *procedimentos, long int *tamprocedimento, long int *codigoatual,
                                    Procedimento *novoprocedimento, AmbienteMedico *ambientes, MedicamentoMaterial *medicamentosmateriais,
                                    long int tamambientes, long int tammedicamentomaterial);
Agendamento *cadastraragendamento(Agendamento *agendamentos, long int *tamagendamentos, long int *codigoatual,
                                  Agendamento *novoagendamento, Paciente *pacientes, long int tampacientes, Profissional *profissionais, long int tamprofissionais,
                                  Procedimento *procedimentos, long int tamprocedimento,
                                  MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial);
Profissional *cadastrarprofissionalsaude(Profissional *profissionais, long int *tamprofisionais, long int *codigoatual, Profissional *novoprofisional);
// edicoes
long int alterarambientemedico(AmbienteMedico *ambientes, long int tamambiente, long int codigo);
long int alterarfornecedor(Fornecedor *fornecedores, long int tamfornecedor, long int codigo);
long int alterarmedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, long int codigo);
long int alterarpaciente(Paciente *pacientes, long int tampacientes, long int codigo);
void alterarprocedimento(Procedimento *procedimentos, long int tamprocedimento, long int codigo); // unica diferente porque dentro dela vc realoca o vetor de códigos e se fosse long int
long int alterarprofissional(Profissional *profisionais, long int tamprofisional, long int codigo);

// listagem
void listarambiente(AmbienteMedico *ambientes, long int tamambiente);
void listarfornecedores(Fornecedor *fornecedores, long int tamfornecedor);
void listarmedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial);
void listarpacientes(Paciente *pacientes, long int tampacientes);
void listarprocedimento(Procedimento *procedimentos, long int tamprocedimento);
void listarprofissional(Profissional *profisionais, long int tamprofisional);

// exclusão
AmbienteMedico *excluirambientemedico(AmbienteMedico *ambientes, long int *tamambiente, int codigo);
Fornecedor *excluirfornecedor(Fornecedor *fornecedores, long int *tamfornecedor, long int codigo);
MedicamentoMaterial *excluimedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int *tammedicamentomaterial, long int codigo);
Paciente *excluirpaciente(Paciente *pacientes, long int *tampacientes, long int codigo);
Procedimento *excluirprocedimento(Procedimento *procedimentos, long int *tamprocedimento, long int codigo);
Profissional *excluirprofissional(Profissional *profisionais, long int *tamprofisional, long int codigo);

// consulta
long int consultaambiente(AmbienteMedico *ambientes, long int tamambiente, long int codigo);
long int consultafornecedor(Fornecedor *fornecedores, long int tamfornecedor, long int codigo);
long int consultamedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, long int codigo);
long int consultapaciente(Paciente *pacientes, long int tampacientes, long int codigo);
long int consultaprocedimento(Procedimento *procedimentos, long int tamprocedimento, long int codigo);
long int consultaprofissional(Profissional *profisionais, long int tamprofisional, long int codigo);

// importar
long int importarpaciente(Paciente **pacientes, char *nome, long int *tampacientes, long int *codigoatual);
long int importarambiente(AmbienteMedico **ambientes, char *nome, long int *tamambientes, long int *codigoatual);
long int importarfornecedor(Fornecedor **fornecedores, char *nome, long int *tamfornecedor, long int *codigoatualfornecedor);
long int importarmedicamento(MedicamentoMaterial **medicamentosmateriais, char *nome, long int *tammedicamentomaterial, long int *codigoatualmedicamentomaterial);
long int importarprofissional(Profissional **profissionais, char *nome, long int *tamprofissionais, long int *codigoatual);
long int importaragendamento(Agendamento **agendamentos, char *nome, long int *tamagendamento, long int *codigoatualagendamento,
                             Paciente *pacientes, long int tampacientes,
                             Profissional *profissionais, long int tamprofissionais,
                             Procedimento *procedimentos, long int tamprocedimento,
                             MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial);
long int importarprocedimento(Procedimento **procedimentos,char *nome,long int *tamprocedimento,long int *codigoatual,AmbienteMedico *ambientes,
    MedicamentoMaterial *medicamentosmateriais,
    long int tamambientes,
    long int tammedicamentomaterial);

    
// exportar
long int exportarpaciente(Paciente *pacientes, char *nome, long int tampacientes);
long int exportarambiente(AmbienteMedico *ambientes, char *nome, long int tamambientes);
long int exportarfornecedor(Fornecedor *fornecedores, char *nome, long int tamfornecedor);
long int exportarmedicamento(MedicamentoMaterial *medicamentosmateriais, char *nome, long int tammedicamentomaterial);
long int exportarprofissional(Profissional *profissionais, char *nome, long int tamprofissionais);
long int exportaragendamento(Agendamento *agendamentos, char *nome, long int tamagendamento);
long int exportarprocedimento(Procedimento *procedimentos, char *nome, long int tamprocedimento);

// abrir arquivos e importar  e exportar txt e bin
long int importarpacientetxt(Paciente **pacientes, long int *tampacientes, long int *codigoatual, char *nome);
void exportarpacientetxt(Paciente *pacientes, char *nome, long int tampacientes);
long int importarfornecedortxt(Fornecedor **fornecedores, long int *tamfornecedores, long int *codigoatual, char *nome);
void exportarfornecedortxt(Fornecedor *fornecedores, char *nome, long int tamfornecedores);
long int importarmedicamentotxt(MedicamentoMaterial **medicamentos, long int *tammedicamentos, long int *codigoatual, char *nome);
void exportarmedicamentotxt(MedicamentoMaterial *medicamentos, char *nome, long int tammedicamentos);
long int importarprofissionaltxt(Profissional **profissionais, long int *tamprofissionais, long int *codigoatual, char *nome);
void exportarprofissionaltxt(Profissional *profissionais, char *nome, long int tamprofissionais);
long int importarpacientetxt(Paciente **pacientes, long int *tampacientes, long int *codigoatual, char *nome);
long int importarambientemedicotxt(AmbienteMedico **ambientes, long int *tamambiente, long int *codigoatual, char *nome);
void exportarambientemedicotxt(AmbienteMedico *ambientes, char *nome, long int tamambiente);
long int importarprocedimentotxt(Procedimento **procedimentos, long int *tamprocedimento, long int *codigoatual, AmbienteMedico *ambientes, MedicamentoMaterial *medicamentosmateriais, long int tamabientes, long int tammedicamento, char *nome);
void exportarprocedimentotxt(Procedimento *procedimentos, long int tam, const char *caminho);
long int importaragendamentotxt(Agendamento **agendamentos, long int *tamagendamentos, long int *codigoatual, char *nome, Paciente *pacientes, long int tampacientes, Profissional *profissionais, long int tamprofissionais, Procedimento *procedimentos, long int tamprocedimento, MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial);
void exportaragendamentotxt(Agendamento *agendamentos, char *nome, long int tamagendamentos);
long int importarrecebertxt(Receber **receber, long int *tamreceber, long int *codigoatual, char *nome, Agendamento *agendamentos, long int tamagendamento, Procedimento *procedimentos, long int tamprocedimento);
void exportarrecebertxt(Receber *receber, char *nome, long int tamreceber);
long int importarentradaestoquetxt(Entradaestoque **entradaestoque, long int *tamentradaestoque, long int *codigoatual, MedicamentoMaterial *medicamentosmateriais, long int tammedicamentosmaterial, char *nome);
long int importarlancamentosretiradastxt(LacamentosRetiradas **lacamentosretiradas, long int *tamlacamentosretiradas,
                                         Agendamento *agendamentos, long int tamagendamento,
                                         Procedimento *procedimentos, long int tamprocedimento,
                                         float *saldototal,
                                         Entradaestoque *entradaestoque, long int tamentradaestoque,
                                         char *nome);
void exportarlancamentosretiradastxt(LacamentosRetiradas *lacamentosretiradas, long int tamlacamentosretiradas, const char *nome);
void exportarentradaestoquetxt(Entradaestoque *entradaestoque, long int tam, const char *caminho);
long int importarpacientebin(Paciente **pacientes, long int *tampacientes, long int *codigoatual, const char *nomearquivo);
void exportarpacientebin(Paciente *pacientes, long int tampacientes, const char *nomearquivo);
long int importarfornecedorbin(Fornecedor **fornecedores, long int *tamfornecedor, long int *codigoatual, const char *nomearquivo);
void exportarfornecedorbin(Fornecedor *fornecedores, long int tamfornecedor, const char *nomearquivo);
long int importarmedicamentomaterialbin(MedicamentoMaterial **medicamentosmateriais, long int *tammedicamentomaterial, long int *codigoatual, const char *nomearquivo);
void exportarmedicamentomaterialbin(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, const char *nomearquivo);
long int importarprofissionalbin(Profissional **profissionais, long int *tamprofissionais, long int *codigoatual, const char *nomearquivo);
void exportarprofissionalbin(Profissional *profissionais, long int tamprofissionais, const char *nomearquivo);
long int importarambientemedicobin(AmbienteMedico **ambientes, long int *tamambiente, long int *codigoatual, const char *nomearquivo);
void exportarambientemedicobin(AmbienteMedico *ambientes, long int tamambiente, const char *nomearquivo);

long int importarprocedimentobin(Procedimento **procedimentos, long int *tamprocedimento, long int *codigoatual,
                                 const char *nomearquivo,
                                 AmbienteMedico *ambientes, long int tamambientes,
                                 MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial);
void exportarprocedimentobin(Procedimento *procedimentos, long int tamprocedimento, const char *nomearquivo);
 

long int importarreceberbin(Receber **receber, long int *tamreceber, long int *codigoatual, const char *nomearquivo, Agendamento *agendamentos, long int tamagendamento, Procedimento *procedimentos, long int tamprocedimento);
void exportarreceberbin(Receber *receber, long int tamreceber, const char *nomearquivo);
long int importarentradaestoquebin(Entradaestoque **entradas, long int *tamentradaestoque, long int *codigoatual,
                                   const char *nomearquivo,
                                   MedicamentoMaterial *medicamentosmateriais, long int tammedicamentosmaterial);
void exportarentradaestoquebin(Entradaestoque *entradas, long int tamentradaestoque, const char *nomearquivo);
long int importarlancamentoretiradabin(
    LacamentosRetiradas **lancamentos, long int *tam,
    Agendamento *agendamentos, long int tamagendamento,
    Procedimento *procedimentos, long int tamprocedimento,
    float *saldototal,
    Entradaestoque *entradaestoque, long int tamentradaestoque, char *nomedoarquivo);
void exportarlancamentoretiradabin(LacamentosRetiradas *lancamentos, long int tam, const char *nomearquivo);
long int importaragendamentobin(Agendamento **agendamentos,long int *tamagendamentos,long int *codigoatual,const char *nomearquivo,Paciente *pacientes,long int tampacientes,Profissional *profissionais,long int tamprofissionais,Procedimento *procedimentos,long int tamprocedimento,MedicamentoMaterial *medicamentosmateriais,long int tammedicamentomaterial);
void exportaragendamentobin(Agendamento *agendamentos, long int tamagendamentos, const char *nomearquivo);
// estoque
Entradaestoque *cadastrarentradaestoque(Entradaestoque *entradaestoque, long int *tamentradaestoque,
                                        MedicamentoMaterial *medicamentosmateriais, long int tammedicamentosmaterial,
                                        Entradaestoque *novoentradaestoque, long int *codigoatual);
void estoqueminimo(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial);
void alterarpreco(Entradaestoque *novoentradaestoque, MedicamentoMaterial *medicamentomaterial,
                  long int tammedicamentomaterial);

// caixa
LacamentosRetiradas *cadastrarlancamentoretirada(LacamentosRetiradas *lacamentosretiradas,
                                                 long int *tamlacamentosretiradas,
                                                 LacamentosRetiradas *novolacamentoretirada, Agendamento *agendamentos,
                                                 long int tamagendamento, Procedimento *procedimentos,
                                                 long int tamprocedimento, float *saldototal, Entradaestoque *entradaestoque, long int tamentradaestoque);

Receber *cadastrarreceber(Receber *receber, long int *tamreceber, long int *codigoatual,
                          Receber *novoreceber, Agendamento *agendamentos, long int tamagendamento,
                          Procedimento *procedimentos, long int tamprocedimento);
long int efetuarpagamento(long int codigoentradaestoque, float *saldototal, char *data, Entradaestoque *entradaestoque, long int tamentradaestoque,
                          LacamentosRetiradas **lancamentosentradas, long int *tamlancamentosentradas);
void imprimirLancamentosRetiradas(LacamentosRetiradas *lancamentos, long int tamlancamentosretiradas);
Receber *excluirreceber(Receber *receber, long int *tamreceber, long int codigo,
                        LacamentosRetiradas **lancamentosentradas, long int *tamlancamentosentradas,
                        float *saldototal, Entradaestoque *entradaestoque, long int tamentradaestoque);
// relatorios (deixei essa parte  aqui porque ela é gigante)
void menurelatorios(Agendamento *agendamentos, long int tamagendamento, AmbienteMedico *ambientes, long int tamambientes,
                    LacamentosRetiradas *lancamentosretiradas, long int tamlacamentosretiradas, Entradaestoque *entradaestoque, long int tamentradaestoque,
                    Fornecedor *fornecedores, long int tamfornecedores, MedicamentoMaterial *medicamentosmariais, long int tammedicamentomaterial,
                    Paciente *pacientes, long int tampaciente, Procedimento *procedimentos, long int tamprocedimento,
                    Profissional *profissionais, long int tamprofissional, Receber *receber, long int tamreceber);

// Relatorio caixa
void relatoriopacientecaixa(Receber *receber, long int tamreceber, Paciente *pacientes, long int tampacientes, Agendamento *agendamentos, long int tamagendamentos, long int paciente, int opcsv);
void relatoriocaixasemfiltro(Receber *receber, long int tamreceber, int opcsv);
// usa essa função pra convertar a data
int converterdata(char *data);
void relatorioreceberdata(Receber *receber, long int tamreceber, char *data1, char *data2, int opcsv);
void relatoriopagarfornecedor(LacamentosRetiradas *lancamentosretiradas, long int tamlacamentoretirada, int opcsv, long int codfornecedor,
                              Entradaestoque *entradaestoque, long int tamentradaestoque);
void relatoriopagardata(LacamentosRetiradas *lancamentosretiradas, long int tamlancamentoretirada, Entradaestoque *entradaestoque,
                        long int tamentradaestoque, char *data1, char *data2, int opcsv);
void relatoriopagarsemfiltro(LacamentosRetiradas *lancamentosretiradas, long int tamlancamentoretirada, Entradaestoque *entradaestoque,
                             long int tamentradaestoque, int opcsv);

void relatorioestoqueprocedimento(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, Procedimento *procedimentos,
                                  long int tamprocedimento, long int codprocedimento, int opcsv);
void relatorioestoquepaciente(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial,
                              Agendamento *agendamentos, long int tamagendamentos,
                              Procedimento *procedimentos, long int tamprocedimento,
                              long int codpaciente, int opcsv);

void relatoriosestoquedata(Entradaestoque *entradaestoque, long int tamentradaestoque, MedicamentoMaterial *medicamentosmateriais, long int tammedicamamentomaterial, char *data1, char *data2, int opcsv);
void relatorioestoqueprofissional(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, Agendamento *agendamentos, long int tamagendamentos,
                                  Procedimento *procedimentos, long int tamprocedimento,
                                  long int codprofissional, int opcsv);
void relatorioestoqueminimo(MedicamentoMaterial *medicamentomaterial, long int tammedicamentomaterial, int opcsv);
void relatorioestoquesemfiltro(MedicamentoMaterial *medicamentomaterial, long int tammedicamentomaterial, int opcsv);

void relatorioprocedimentoprocedimento(Agendamento *agendamentos, long int tamagendamento, Procedimento *procedimentos, long int tamprocedimento, long int codprocedimento, int opcsv);
void relatorioprocedimentopaciente(Agendamento *agendamentos, long int tamagendamento, Procedimento *procedimentos, long int tamprocedimento, Paciente *pacientes, long int tampacientes, long int codpaciente, int opcsv);
void relatorioprocedimentodata(Agendamento *agendamentos, long int tamagendamento, Procedimento *procedimentos, long int tamprocedimento, char *data1, char *data2, int opcsv);
void relatorioprocedimentoprofissional(Agendamento *agendamentos, long int tamagendamento, Procedimento *procedimentos, long int tamprocedimento, Profissional *profissional, long int tamprofissional, long int codprofissional, int opcsv);
void relatorioprocedimentosemfiltro(Agendamento *agendamentos, long int tamagendamento, Procedimento *procedimentos, long int tamprocedimento, int opcsv);

// relatorios basicos
void relatoriobasicopacientecidade(Paciente *pacientes, long int tampacientes, char *cidade, int opcsv);
void relatoriobasicopacientesemfiltro(Paciente *paciente, long int tampacientes, int opscv);
void relatoriosbasicofornecedores(Fornecedor *fornecedores, long int tamfornecedores, char *estado, int opcsv);
void relatoriosbasicosfornecedoressemfiltro(Fornecedor *fornecedores, long int tamornecedor, int opcsv);
void relatoriobasicoambientes(AmbienteMedico *ambientes, long int tamabiente, int opcsv);
void relatoriobasicomedicamentomaterialfornecedor(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, long int codfornecedor, int opcsv);
void relatoriobasicomedicamentomaterialsemfiltro(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, int opcsv);
void relatoriobasicoprocedimentoambiente(Procedimento *procedimentos, long int tamprocedimento, long int codambiente, int opcsv);
void relatoriobasicoprocedimentosemfiltro(Procedimento *procedimentos, long int tamprocedimento, int opcsv);
void relatoriobasicoprofissionaisespecialidade(Profissional *profissionais, long int tamprofissionais, char *especialidade, int opcsv);
void relatoriobasicoprofissionaissemfiltro(Profissional *profissionais, long int tamprofissionais, int opcsv);

#endif