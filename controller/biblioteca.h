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
    char rua[200];
    char bairro[200];
    char cidade[200];
    char estado[10]; // Ex: "SP"
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
    long int *codmedicamentosemateriais; // esse vai ser um ponteiro para um vetor de codigos de maedicamentos e materiais
    long int codambientemedico;          // codigo do ambiente medico
    long int tamcodmedicamentosmateriais;
} Procedimento;
 

typedef struct{
 long int codigo,codpaciente, codprofissional,codprocedimento;
 char data[20],horario[20];
}Agendamento;


// menus auxiliares memoria
void menuambientesmedicos(AmbienteMedico **ambientes, long int *tamambiente, long int *codigoatual);
void menufornecedores(Fornecedor **fornecedores, long int *tamfornecedor, long int *codigoatatual);
void menumedicamentos_materiais(MedicamentoMaterial **medicamentosmateriais, long int *tammedicamentomaterial,long int *codigoatual);
void menuPacientes(Paciente **pacientes, long int *tampacientes,long int *codigoatual);
void menuprocedimentos(Procedimento **procedimentos, long int *tamprocedimento, long int *codigoatual);
void menuprofisionais(Profissional **profissionais, long int *tamprofissionais, long int *codigoatual);

void menuagendamento_controle(Agendamento **agendamentos,long int *tamagendamento,long int *codigoatual,Procedimento *procedimentos,
long int *tamprocedimento,MedicamentoMaterial *medicamentosmateriais,
long int tammedicamentomaterial,Paciente *pacientes,long int tampacientes,
Profissional *profissionais,long int tamprofissionais);

// menus auxiliares de arquivo
void menuagendamento_controle_arquivo(int oparquivo);

// cadastros
AmbienteMedico *cadastrarambientemedico(AmbienteMedico *ambientes, long int *tamambiente, long int *codigoatual, AmbienteMedico *novoambiente);
Fornecedor *cadastrarfornecedor(Fornecedor *fornecedores, long int *tamfornecedor, long int *codigoatual,Fornecedor *novofornecedor);
MedicamentoMaterial *cadastrarmedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int *tammedicamentomaterial, long int *codigoatual, MedicamentoMaterial *novomedicamentomaterial);
Paciente *cadastrarpaciente(Paciente *pacientes, long int *tampacientes, long int *codigoatual,Paciente *novopaciente);
Procedimento *cadastrarprocedimento(Procedimento *procedimentos, long int *tamprocedimento, long int *codigoatual, Procedimento *novoprocedimento);
Profissional *cadastrarprofissionalsaude(Profissional *profissionais, long int *tamprofisionais, long int *codigoatual,Profissional *novoprofisional);
// edicoes
long int alterarambientemedico(AmbienteMedico *ambientes, long int tamambiente, long int codigo);
long int alterarfornecedor(Fornecedor *fornecedores, long int tamfornecedor, long int codigo);
long int alterarmedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, long int codigo);
long int alterarpaciente(Paciente *pacientes, long int tampacientes, long int codigo);
void alterarprocedimento(Procedimento *procedimentos, long int tamprocedimento, long int codigo);//unica diferente porque dentro dela vc realoca o vetor de códigos e se fosse long int
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



#endif