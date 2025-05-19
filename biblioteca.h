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
    char bairro[40];
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
    char crm[20];
    char especialidade[200];
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
    char cnpj[20];
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
    char descricao[1000];
    float custo;
    long int tempoEstimado;
    long int *codmedicamentosemateriais; // esse vai ser um ponteiro para um vetor de codigos de maedicamentos e materiais
    long int codambientemedico;          // codigo do ambiente medico
    long int tamcodmedicamentosmateriais;
} Procedimento;

// menus auxiliares
void menuambientesmedicos();
void menufornecedores();
void menumedicamentos_materiais();
void menuPacientes();
void menuprocedimentos();
void menuprofisionais();

// cadastros
AmbienteMedico *cadastrarambientemedico(AmbienteMedico *ambientes, long int *tamambiente, long int *codigoatual);
Fornecedor *cadastrarfornecedor(Fornecedor *fornecedores, long int *tamfornecedor, long int *codigoatual);
MedicamentoMaterial *cadastrarmedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int *tammedicamentomaterial, long int *codigoatual);
Paciente *cadastrarpaciente(Paciente *pacientes, long int *tampacientes, long int *codigoatual);
Procedimento *cadastrarprocedimento(Procedimento *procedimentos, long int *tamprocedimento, long int *codigoatual);
Profissional *cadastrarprofissionalsaude(Profissional *profissionais, long int *tamprofisionais, long int *codigoatual);

// edicoes
void alterarambientemedico(AmbienteMedico *ambientes, long int tamambiente, long int codigo);
void alterarfornecedor(Fornecedor *fornecedores, long int tamfornecedor, long int codigo);
void alterarmedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial, long int codigo);
void alterarpaciente(Paciente *pacientes, long int tampacientes, long int codigo);
void alterarprocedimento(Procedimento *procedimentos, long int tamprocedimento, long int codigo);
void alterarprofissional(Profissional *profisionais, long int tamprofisional, long int codigo);

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
Profissional *excluirprofisional(Profissional *profisionais, long int *tamprofisional, long int codigo);

// consulta
void consultaambiente(AmbienteMedico *ambientes,long int tamambiente ,long int codigo);
void consultafornecedor(Fornecedor *fornecedores, long int tamfornecedor,long int codigo);
void consultamedicamentomaterial(MedicamentoMaterial *medicamentosmateriais, long int tammedicamentomaterial,long int codigo);
void consultapaciente(Paciente *pacientes,long int tampacientes,long int codigo);
void consultaprocedimento(Procedimento *procedimentos,long int tamprocedimento,long int codigo);
void consultaprofisional(Profissional *profisionais, long int tamprofisional, long int codigo);


#endif