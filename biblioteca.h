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
    char rua[100];
    char bairro[50];
    char cidade[50];
    char estado[3]; // Ex: "SP"
} Endereco;

typedef struct
{
    long int codigo;
    char nomeCompleto[100];
    int cpf[15];
    Endereco endereco;
    long int telefone[20];
    char dataNascimento[11];
    char historicoMedico[2000];
} Paciente;

typedef struct
{
    long int codigo;
    char nomeCompleto[100];
    char crm[20];
    char especialidade[50];
    int cpf[15];
    long int telefone[20];
    char email[100];
} Profissional;

typedef struct
{
    long int codigo;
    char nomeFantasia[100];
    char razaoSocial[100];
    char inscricaoEstadual[20];
    char cnpj[20];
    Endereco endereco;
    char telefone[20];
    char email[100];
} Fornecedor;

typedef struct
{
    long int codigo;
    char descricaoProcedimento[1000];
} AmbienteMedico;

typedef struct
{
    long int codigo;
    char descricao[100];
    char fabricante[50];
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
    long int quantidadeItens;
    AmbienteMedico ambientemedico;
} Procedimento;

// menus auxiliares
void menuambientesmedicos();
void menufornecedores();
void menumedicamentos_materiais();
void menuPacientes();
void menuprocedimentos();
void menuprofisionais();

// cadastros
AmbienteMedico *cadastrarambientemedico(AmbienteMedico *ambientes, long int *tamambientes);
Fornecedor *cadastrarfornecedor(Fornecedor *fornecedores, long int *tamfornecedor);
MedicamentoMaterial *cadastrarmedicamentomaterial(MedicamentoMaterial *itens, long int *tammedicamentomaterial);
Paciente *cadastrarpaciente(Paciente *pacientes, long int *tampacientes);
Procedimento *cadastrarprocedimento(Procedimento *procedimentos, long int *tamprocedimento);
Profissional *cadastrarprofissionalsaude(Profissional *profissionais, long int *tamprocedimento);

// edicoes
Paciente *altererpaciente(Paciente *pacientes, long int *tampacientes, int cpf);

#endif