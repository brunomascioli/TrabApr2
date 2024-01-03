#include <locale.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef struct {
  double cpf;
  char nome[150], dataNascimento[12], sexo[15], email[256], telefone[50];
} Aluno;

typedef struct {
  int codigo;
  char descricao[300], nomeCurso[75];
  int cargaHoraria;
  float precoCurso;
} Curso;

typedef struct {
  double cpfAluno;
  int codigoCurso;
  char dataInicio[20];
  char dataTermino[20];
  float desconto;
} Matricula;

void menu() {
  int opc;
  printf("=========== Menu principal =========== \n");
  printf("\t1. Submenu de Alunos\n");
  printf("\t2. Submenu de Cursos\n");
  printf("\t3. Submenu de Matrícula\n");
  printf("\t4. Submenu de Relatórios\n");
  printf("\t5. Sair\n");
  printf("-> ");
}

void submenuInterface(char str[]) {
  printf("=========== Submenu de %s ===========\n", str);
  printf("\t1. Listar todos\n");
  printf("\t2. Listar um\n");
  printf("\t3. Incluir\n");
  printf("\t4. Alterar\n");
  printf("\t5. Excluir\n");
  printf("\t6. Menu principal\n");
  printf("-> ");
}

////////// Funcoes de Alunos //////////

int cpfExiste(Aluno **alunosCadastrados, int qtd_alunos, double cpf) {
  int i;
  for (i = 0; i < qtd_alunos; i++) {
    if ((*alunosCadastrados)[i].cpf == cpf) {
      return i;
    }
  }
  return -1;
}

void listarAlunos(Aluno **alunosCadastrados, int *qtd_alunos) {
  if (*qtd_alunos > 0) {
    for (int i = 0; i < *qtd_alunos; i++) {
      printf("=========================================\n\n");
      printf("Aluno %d:\n", i + 1);
      printf("Nome: %s\n", (*alunosCadastrados)[i].nome);
      printf("Data de nascimento: %s\n",
             (*alunosCadastrados)[i].dataNascimento);
      printf("CPF: %.0f\n", (*alunosCadastrados)[i].cpf);
      printf("Sexo: %s\n", (*alunosCadastrados)[i].sexo);
      printf("Email: %s\n", (*alunosCadastrados)[i].email);
      printf("Telefone: %s\n\n", (*alunosCadastrados)[i].telefone);
    }
  } else {
    printf("Nenhum aluno cadastrado!\n\n");
  }
}

void listarUmAluno(Aluno **alunosCadastrados, int *qtd_alunos) {
  double id;
  printf("Digite o CPF do aluno que deseja consultar: ");
  scanf("%lf", &id);
  system(CLEAR);
  int index_aluno = -1;
  for (int i = 0; i < *qtd_alunos; i++) {
    if ((*alunosCadastrados)[i].cpf == id) {
      index_aluno = i;
      break;
    }
  }
  if (index_aluno != -1) {
    printf("\nAluno encontrado!\n");
    printf("Nome: %s\n", (*alunosCadastrados)[index_aluno].nome);
    printf("Data de nascimento: %s\n",
           (*alunosCadastrados)[index_aluno].dataNascimento);
    printf("CPF: %.0f\n", (*alunosCadastrados)[index_aluno].cpf);
    printf("Sexo: %s\n", (*alunosCadastrados)[index_aluno].sexo);
    printf("Email: %s\n", (*alunosCadastrados)[index_aluno].email);
    printf("Telefone: %s\n\n", (*alunosCadastrados)[index_aluno].telefone);
  } else {
    printf("Aluno não encontrado!\n");
  }
}

void incluirAluno(Aluno **alunosCadastrados, int *qtd_alunos) {
  Aluno novoAluno;
  system(CLEAR);
  printf("Cpf (Ex:33322244455): ");
  scanf("%lf", &novoAluno.cpf);
  getchar();
  if (cpfExiste(alunosCadastrados, *qtd_alunos, novoAluno.cpf) == -1) {
    printf("Nome: ");
    gets(novoAluno.nome); 
    printf("Data de nascimento: ");
    scanf("%s", novoAluno.dataNascimento);
    printf("Sexo: ");
    scanf("%s", novoAluno.sexo);
    printf("Email: ");
    scanf("%s", novoAluno.email);
    printf("Telefone (Exemplo: 16998877555): ");
    scanf("%s", novoAluno.telefone);
    (*qtd_alunos)++;
    *alunosCadastrados =
        realloc(*alunosCadastrados, *qtd_alunos * sizeof(Aluno));
    if (*alunosCadastrados != NULL) {
      (*alunosCadastrados)[(*qtd_alunos) - 1] = novoAluno;
      printf("\nAluno cadastrado com sucesso\n\n");
    } else {
      printf("Falha ao realocar memória.\n");
    }
  } else {
    printf("Esse CPF já está cadastrado\n\n");
  }
}

void alterarAluno(Aluno **alunosCadastrados, int *qtd_alunos) {
  double id;
  system(CLEAR);
  printf("Digite o CPF do aluno que deseja alterar: ");
  scanf("%lf", &id);
  int index_aluno = -1;
  for (int i = 0; i < *qtd_alunos; i++) {
    if ((*alunosCadastrados)[i].cpf == id) {
      index_aluno = i;
      break;
    }
  }
  getchar();
  if (index_aluno != -1) {
    printf("Alterando os valores\n");
    printf("Nome: ");
    gets((*alunosCadastrados)[index_aluno].nome);
    printf("Data de nascimento: ");
    scanf("%s", (*alunosCadastrados)[index_aluno].dataNascimento);
    printf("Sexo: ");
    scanf("%s", (*alunosCadastrados)[index_aluno].sexo);
    printf("Email: ");
    scanf("%s", (*alunosCadastrados)[index_aluno].email);
    printf("Telefone (Exemplo: 16998877555): ");
    scanf("%s", (*alunosCadastrados)[index_aluno].telefone);
  } else {
    printf("Aluno não encontrado!\n");
  }
}

void excluirAluno(Aluno **alunosCadastrados, int *qtd_alunos) {
  double id;
  system(CLEAR);
  printf("Digite o CPF do aluno que deseja excluir: ");
  scanf("%lf", &id);
  int index_aluno = -1;
  for (int i = 0; i < *qtd_alunos; i++) {
    if ((*alunosCadastrados)[i].cpf == id) {
      index_aluno = i;
      break;
    }
  }
  if (index_aluno != -1) {
    int i;
    for (i = index_aluno; i < *qtd_alunos; i++) {
      (*alunosCadastrados)[i] = (*alunosCadastrados)[i + 1];
    }
    (*qtd_alunos)--;
    *alunosCadastrados =
        realloc(*alunosCadastrados, (*qtd_alunos * sizeof(Aluno)));
    ;
    printf("\nAluno removido com sucesso!\n\n");
  } else {
    printf("Aluno não encontrado!\n");
  }
}

void subMenuAlunos(Aluno **alunosCadastrados, int *qtd_alunos) {
  char nome[] = "Alunos";
  submenuInterface(nome);
  int opc;
  scanf("%d", &opc);
  system(CLEAR);
  switch (opc) {
  case 1:
    listarAlunos(alunosCadastrados, qtd_alunos);
    break;
  case 2:
    listarUmAluno(alunosCadastrados, qtd_alunos);
    break;
  case 3:
    incluirAluno(alunosCadastrados, qtd_alunos);
    break;
  case 4:
    alterarAluno(alunosCadastrados, qtd_alunos);
    break;
  case 5:
    excluirAluno(alunosCadastrados, qtd_alunos);
    break;
  case 6:
    system(CLEAR);
    return;
    break;
  default:
    printf("\nOpção Inválida\n\n");
    break;
  }
}

////////// Funções de Curso //////////

void listarCursos(Curso **cursosCadastrados, int *qtd_cursos) {
  if (*qtd_cursos > 0) {
    for (int i = 0; i < *qtd_cursos; i++) {
      printf("=========================================\n\n");
      printf("Curso %d:\n", i + 1);
      printf("Nome: %s\n", (*cursosCadastrados)[i].nomeCurso);
      printf("Código: %d\n", (*cursosCadastrados)[i].codigo);
      printf("Descrição: %s\n", (*cursosCadastrados)[i].descricao);
      printf("Carga Horária (em horas): %d\n",
             (*cursosCadastrados)[i].cargaHoraria);
      printf("Preço: %.2f\n\n", (*cursosCadastrados)[i].precoCurso);
    }
  } else {
    printf("Nenhum curso foi cadastrado!\n\n");
  }
}

void listarUmCurso(Curso **cursosCadastrados, int *qtd_alunos) {
  unsigned int codigo;
  printf("Digite o código do curso que deseja consultar: ");
  scanf("%d", &codigo);
  int index_curso = -1;
  for (int i = 0; i < *qtd_alunos; i++) {
    if ((*cursosCadastrados)[i].codigo == codigo) {
      index_curso = i;
      break;
    }
  }
  if (index_curso != -1) {
    printf("\nCurso encontrado!\n");
    printf("Nome: %s\n", (*cursosCadastrados)[index_curso].nomeCurso);
    printf("Código: %d\n", (*cursosCadastrados)[index_curso].codigo);
    printf("Descrição: %s\n", (*cursosCadastrados)[index_curso].descricao);
    printf("Carga Horária (em horas): %d\n",
           (*cursosCadastrados)[index_curso].cargaHoraria);
    printf("Preço: %.2f\n\n", (*cursosCadastrados)[index_curso].precoCurso);
  } else {
    printf("Curso não encontrado!\n");
  }
}

int codigoExiste(Curso **cursos, int qtd_cursos, int codigo) {
  for (int i = 0; i < qtd_cursos; i++) {
    if ((*cursos)[i].codigo == codigo) {
      return 1;
    }
  }
  return -1;
}

void incluirCurso(Curso **cursos, int *qtd_cursos) {
  Curso novoCurso;
  int codigo;
  printf("Código: ");
  scanf("%d", &codigo);

  if (codigoExiste(cursos, *qtd_cursos, codigo) == 1) {
    printf("Esse código já está cadastrado!\n\n");
    return;
  }

  novoCurso.codigo = codigo;
  getchar();
  printf("Nome: ");
  gets(novoCurso.nomeCurso);
  printf("Descrição: ");
  gets(novoCurso.descricao);
  printf("Carga Horária (em horas): ");
  scanf("%d", &novoCurso.cargaHoraria);
  printf("Preço: ");
  scanf("%f", &novoCurso.precoCurso);
  (*qtd_cursos)++;
  *cursos = realloc(*cursos, *qtd_cursos * sizeof(Curso));
  if (cursos != NULL) {
    (*cursos)[(*qtd_cursos) - 1] = novoCurso;
    printf("\nCurso cadastrado com sucesso\n\n");
  } else {
    printf("Falha ao realocar memória.\n");
  }
}

void alterarCurso(Curso **cursos, int *qtd_cursos) {
  unsigned int id;
  printf("Digite o código do curso que deseja alterar: ");
  scanf("%d", &id);
  int index_curso = -1;
  for (int i = 0; i < *qtd_cursos; i++) {
    if ((*cursos)[i].codigo == id) {
      index_curso = i;
      break;
    }
  }
  if (index_curso != -1) {
    getchar();
    printf("Alterando os valores\n");
    printf("Nome: ");
    gets((*cursos)[index_curso].nomeCurso);
    printf("Descrição: ");
    gets((*cursos)[index_curso].descricao);
    printf("Carga Horaria (em horas): ");
    scanf("%d", &((*cursos)[index_curso].cargaHoraria));
    printf("Preco: ");
    scanf("%f", &((*cursos)[index_curso].precoCurso));
    printf("\n");
  } else {
    printf("Curso não encontrado!\n");
  }
}

void excluirCurso(Curso **cursosCadastrados, int *qtd_cursos) {
  unsigned int codigo;
  Curso *temp;
  printf("Digite o código do curso que deseja excluir: ");
  scanf("%d", &codigo);
  int index_curso = -1;
  for (int i = 0; i < *qtd_cursos; i++) {
    if ((*cursosCadastrados)[i].codigo == codigo) {
      index_curso = i;
      break;
    }
  }
  if (index_curso != -1) {
    for (int i = index_curso; i < *qtd_cursos; i++) {
      (*cursosCadastrados)[i] = (*cursosCadastrados)[i + 1];
    }
    (*qtd_cursos)--;
    *cursosCadastrados =
        realloc(*cursosCadastrados, (*qtd_cursos * sizeof(Curso)));
    printf("\nCurso removido com sucesso!\n\n");
  } else {
    printf("Curso não encontrado!\n");
  }
}

void subMenuCursos(Curso **cursos, int *qtd_cursos) {
  char nome[] = "Cursos";
  submenuInterface(nome);
  int opc;
  scanf("%d", &opc);
  system(CLEAR);
  switch (opc) {
  case 1:
    listarCursos(cursos, qtd_cursos);
    break;
  case 2:
    listarUmCurso(cursos, qtd_cursos);
    break;
  case 3:
    incluirCurso(cursos, qtd_cursos);
    break;
  case 4:
    alterarCurso(cursos, qtd_cursos);
    break;
  case 5:
    excluirCurso(cursos, qtd_cursos);
    break;
  case 6:
    system(CLEAR);
    return;
    break;
  default:
    printf("\nOpção inválida!\n\n");
    break;
  }
}

////////// Funções de Matrícula //////////
void listarMatriculas(Matricula **matriculasCadastradas, int *qtd_matriculas) {
  if (*qtd_matriculas > 0) {
    for (int i = 0; i < *qtd_matriculas; i++) {
      printf("=========================================\n\n");
      printf("CPF: %.0f\n", (*matriculasCadastradas)[i].cpfAluno);
      printf("Código do curso: %d\n", (*matriculasCadastradas)[i].codigoCurso);
      printf("Data de Início: %s\n", (*matriculasCadastradas)[i].dataInicio);
      printf("Data de Término: %s\n", (*matriculasCadastradas)[i].dataTermino);
      printf("Desconto: %.2f\n\n", (*matriculasCadastradas)[i].desconto);
    }
  } else {
    printf("Ainda não tem nenhum aluno cadastrado!\n\n");
  }
}

void listarUmaMatricula(Matricula **matriculasCadastradas,
                        int *qtd_matriculas) {
  double id;
  int codigo;
  printf("Digite o CPF do aluno que você quer consultar a matrícula: ");
  scanf("%lf", &id);
  printf("Digite o código do curso: ");
  scanf("%d", &codigo);
  int index_matricula = -1;
  for (int i = 0; i < *qtd_matriculas; i++) {
    if ((*matriculasCadastradas)[i].cpfAluno == id &&
        (*matriculasCadastradas)[i].codigoCurso == codigo) {
      index_matricula = i;
      break;
    }
  }
  if (index_matricula != -1) {
    printf("\nMatrícula encontrada!\n");
    printf("CPF: %.0f\n", (*matriculasCadastradas)[index_matricula].cpfAluno);
    printf("Código do curso: %d\n",
           (*matriculasCadastradas)[index_matricula].codigoCurso);
    printf("Data de Início: %s\n",
           (*matriculasCadastradas)[index_matricula].dataInicio);
    printf("Data de Término: %s\n",
           (*matriculasCadastradas)[index_matricula].dataTermino);
    printf("Desconto: %.2f\n\n",
           (*matriculasCadastradas)[index_matricula].desconto);
  } else {
    printf("Aluno não encontrado!\n");
  }
}

void incluirMatricula(Matricula **matriculasCadastradas, int *qtd_matriculas,
                      Aluno **alunosCadastrados, int qtd_alunos,
                      Curso **cursosCadastrados, int qtd_cursos) {
  Matricula novaMatricula;
  printf("CPF: ");
  scanf("%lf", &novaMatricula.cpfAluno);
  printf("Código do curso: ");
  scanf("%d", &novaMatricula.codigoCurso);
  printf("Data de início: ");
  scanf(" %[^\n]", novaMatricula.dataInicio);
  printf("Data de término: ");
  scanf("%s", novaMatricula.dataTermino);
  printf("Desconto: ");
  scanf("%f", &novaMatricula.desconto);

  if (codigoExiste(cursosCadastrados, qtd_cursos, novaMatricula.codigoCurso) ==
      -1) {
    printf("O código do curso ainda não está cadastrado!\n\n");
    return;
  }

  if (cpfExiste(alunosCadastrados, qtd_alunos, novaMatricula.cpfAluno) == -1) {
    printf("O CPF ainda não está cadastrado!\n\n");
    return;
  }
  // verificando se a matricula já existe.
  // caso a matricula ja exista a funcao é encerrada
  for (int i = 0; i < *qtd_matriculas; i++) {
    if ((*matriculasCadastradas)[i].cpfAluno == novaMatricula.cpfAluno &&
        (*matriculasCadastradas)[i].codigoCurso == novaMatricula.codigoCurso) {
      printf("Matricula com cpf %.0f e código %d já existe\n",
             novaMatricula.cpfAluno, novaMatricula.codigoCurso);
      return;
    }
  }
  
  *matriculasCadastradas = realloc(*matriculasCadastradas,
                                   ((*qtd_matriculas) + 1) * sizeof(Matricula));
  
  if (*matriculasCadastradas != NULL) {
    (*matriculasCadastradas)[(*qtd_matriculas)] = novaMatricula;
    (*qtd_matriculas)++;
    printf("\nMatrícula cadastrada com sucesso\n\n");
  } else {
    printf("\n\nFalha ao realocar memória\n");
  }
}

void alterarMatricula(Matricula **matriculasCadastradas, int *qtd_matriculas) {
  double id;
  int codigo;
  printf("Digite o CPF do aluno que deseja alterar a matrícula: ");
  scanf("%lf", &id);
  printf("Digite o código do curso: ");
  scanf("%d", &codigo);
  int index_matricula = -1;
  for (int i = 0; i < *qtd_matriculas; i++) {
    if ((*matriculasCadastradas)[i].cpfAluno == id &&
        (*matriculasCadastradas)[i].codigoCurso == codigo) {
      index_matricula = i;
      break;
    }
  }
  if (index_matricula != -1) {
    printf("Alterando os valores\n");
    printf("Data de início: ");
    scanf("%s", (*matriculasCadastradas)[index_matricula].dataInicio);
    printf("Data de término: ");
    scanf("%s", (*matriculasCadastradas)[index_matricula].dataTermino);
    printf("Desconto: ");
    scanf("%f", &(*matriculasCadastradas)[index_matricula].desconto);
  } else {
    printf("Matrícula não encontrada\n");
  }
}

void excluirMatricula(Matricula **matriculasCadastradas, int *qtd_matriculas) {
  double id;
  int codigo;
  int i;
  printf("Digite o CPF do aluno que você quer excluir a matrícula: ");
  scanf("%lf", &id);
  printf("Digite o código do curso: ");
  scanf("%d", &codigo);
  int index_matricula = -1;
  for (i = 0; i < *qtd_matriculas; i++) {
    if ((*matriculasCadastradas)[i].cpfAluno == id &&
        (*matriculasCadastradas)[i].codigoCurso == codigo) {
      index_matricula = i;
      break;
    }
  }
  if (index_matricula != -1) {
    for (i = index_matricula; i < *qtd_matriculas; i++) {
      (*matriculasCadastradas)[i] = (*matriculasCadastradas)[i + 1];
    }
    *matriculasCadastradas =
        realloc(*matriculasCadastradas, (*qtd_matriculas * sizeof(Matricula)));
    (*qtd_matriculas)--;
    printf("\nMatrícula removida com sucesso!\n\n");
  } else {
    printf("\nMatricula não encontrada\n\n");
  }
}

void subMenuMatriculas(Matricula **matriculas, int *qtd_matriculas,
                       Aluno **alunos, int qtd_alunos, Curso **cursos,
                       int qtd_cursos) {
  char nome[] = "Matriculas";
  submenuInterface(nome);
  int opc;
  scanf("%d", &opc);
  system(CLEAR);
  switch (opc) {
  case 1:
    listarMatriculas(matriculas, qtd_matriculas);
    break;
  case 2:
    listarUmaMatricula(matriculas, qtd_matriculas);
    break;
  case 3:
    incluirMatricula(matriculas, qtd_matriculas, alunos, qtd_alunos, cursos,
                     qtd_cursos);
    break;
  case 4:
    alterarMatricula(matriculas, qtd_matriculas);
    break;
  case 5:
    excluirMatricula(matriculas, qtd_matriculas);
    break;
  case 6:
    system(CLEAR);
    return;
    break;
  default:
    printf("\nOpção inválida!\n\n");
    break;
  }
}

////////// Funções de Relatório //////////

void listarAlunosPorCurso(Curso *cursosCadastrados, int qtd_cursos,
                          Aluno *alunosCadastrados, int qtd_alunos,
                          Matricula *matriculasCadastradas,
                          int qtd_matriculas) {
  int cod, i, j;
  printf("Insira o código do curso: ");
  scanf("%d", &cod);
  int index_curso = -1;
  for (i = 0; i < qtd_cursos; i++) {
    if (cursosCadastrados[i].codigo == cod) {
      index_curso = i;
      break;
    }
  }
  int cont = 1;
  if (index_curso != -1) {
    // Abrindo arquivo
    printf("Digite o nome do arquivo para salvar o relatório (digite um nome "
           "de arquivo já existente caso queira sobrescrevê-lo: ");
    char nomeArquivo[256]; // máximo de caracteres para arquivo
    scanf("%s", nomeArquivo);
    strcat(nomeArquivo, ".txt");
    FILE *arqRelatorio;
    char aux[50];
    arqRelatorio = fopen(nomeArquivo, "w");
    int index_matricula = -1, index_aluno = -1;
    for (i = 0; i < qtd_matriculas; i++) {
      index_matricula = -1;
      if (matriculasCadastradas[i].codigoCurso == cod) {
        index_matricula = i;
        for (j = 0; j < qtd_alunos; j++) {
          if (alunosCadastrados[j].cpf ==
              matriculasCadastradas[index_matricula].cpfAluno) {
            printf("=========================================\n");
            printf("\nMatrícula %d:\n", cont);
            printf("Nome do curso: %s\n",
                   cursosCadastrados[index_curso].nomeCurso);
            printf("Nome do aluno: %s\n", alunosCadastrados[j].nome);
            printf("CPF: %.0f\n", alunosCadastrados[j].cpf);
            printf("Email: %s\n", alunosCadastrados[j].email);
            printf("\n\n");

            // Escrevendo no arquivo
            fputs("=========================================\n", arqRelatorio);
            fputs("\nMatrícula: ", arqRelatorio);
            fprintf(arqRelatorio, "%d", cont);
            fputs("\nNome do curso: ", arqRelatorio);
            fputs(cursosCadastrados[index_curso].nomeCurso, arqRelatorio);
            fputs("\nNome do aluno: ", arqRelatorio);
            fputs(alunosCadastrados[j].nome, arqRelatorio);
            fputs("\nCPF: ", arqRelatorio);
            fprintf(arqRelatorio, "%.0f", alunosCadastrados[j].cpf);
            fputs("\nEmail: ", arqRelatorio);
            fputs(alunosCadastrados[j].email, arqRelatorio);
            fputs("\n\n", arqRelatorio);
            cont++;
          }
        }
      }
    }
    fclose(arqRelatorio);
  } else {
    printf("Código de curso não existe.\n\n");
  }
}

time_t dataParaSegundo(char str[]) {
  struct tm data = {0};
  char *ptr_data = strtok(str, "/");

  int j = 0;
  long int valorData;
  time_t somaSegundos = 0;

  while (ptr_data != NULL) {
    valorData = atoi(ptr_data);
    ptr_data = strtok(NULL, "/"); 
    if (j == 0) {
      data.tm_mday = valorData;
    } else if (j == 1) {
      data.tm_mon = valorData - 1;
    } else {
      data.tm_year = valorData - 1900;
    }
    j++;
  }
  somaSegundos = mktime(&data);
  return somaSegundos;
}

void listarCursoPorData(Matricula *matriculasCadastradas,
                        Curso *cursosCadastrados, int qtd_matriculas,
                        int qtd_cursos) {

  struct tm dataInicio = {0};
  struct tm dataTermino = {0};

  printf("Digite a data de início (dd/mm/aaaa): ");
  scanf("%d/%d/%d", &dataInicio.tm_mday, &dataInicio.tm_mon,
        &dataInicio.tm_year);
  printf("Digite a data de término (dd/mm/aaaa): ");
  scanf("%d/%d/%d", &dataTermino.tm_mday, &dataTermino.tm_mon,
        &dataTermino.tm_year);
  dataInicio.tm_year -= 1900;
  dataTermino.tm_year -= 1900;
  dataInicio.tm_mon -= 1;
  dataTermino.tm_mon -= 1;

  time_t segundosInicio = mktime(&dataInicio);
  time_t segundosTermino = mktime(&dataTermino);

  char strInicio[25];
  char strTermino[25];
  char *data;
  time_t dataInicio_matricula, dataTermino_matricula;

  int vetCursos[qtd_cursos];
  int encontrou = 0, cont = 0;

  for (int i = 0; i < qtd_matriculas; i++) {
    strcpy(strInicio, matriculasCadastradas[i].dataInicio);
    strcpy(strTermino, matriculasCadastradas[i].dataTermino);

    dataInicio_matricula = dataParaSegundo(strInicio);
    dataTermino_matricula = dataParaSegundo(strTermino);

    if (dataInicio_matricula >= segundosInicio &&
        dataTermino_matricula <= segundosTermino) {
      if (cont == 0) {
        vetCursos[cont] = matriculasCadastradas[i].codigoCurso;
        cont++;
      } else {
        int aux = 0, encontrou = 0;
        while (aux < cont) {
          if (vetCursos[aux] == matriculasCadastradas[i].codigoCurso) {
            encontrou = 1;
            break;
          }
          aux++;
        }
        if (encontrou == 0) {
          vetCursos[cont] = matriculasCadastradas[i].codigoCurso;
          cont++;
        }
      }
    }
  }

  if (cont == 0) {
    printf("Nenhum curso encontrado no intervalo informado!\n");
    return;
  }

  printf("Digite o nome do arquivo para salvar o relatório (digite um nome "
         "de arquivo já existente caso queira sobrescrevê-lo: ");
  char nomeArquivo[256];
  scanf("%s", nomeArquivo);
  strcat(nomeArquivo, ".txt");
  FILE *arqRelatorio;
  char aux[50];
  arqRelatorio = fopen(nomeArquivo, "w");

  for (int i = 0; i < cont; i++) {
    for (int j = 0; j < qtd_cursos; j++) {
      if (cursosCadastrados[j].codigo == vetCursos[i]) {
        printf("=========================================\n");
        printf("\nCurso: %s\n", cursosCadastrados[j].nomeCurso);
        printf("Código: %d\n", cursosCadastrados[j].codigo);
        printf("Descrição: %s\n", cursosCadastrados[j].descricao);
        printf("Carga Horária: %d\n", cursosCadastrados[j].cargaHoraria);
        printf("Preço: %.2f\n\n", cursosCadastrados[j].precoCurso);

        fputs("=========================================\n", arqRelatorio);
        fprintf(arqRelatorio, "\nCurso: %s\n", cursosCadastrados[j].nomeCurso);
        fprintf(arqRelatorio, "Código: %d\n", cursosCadastrados[j].codigo);
        fprintf(arqRelatorio, "Descrição: %s\n",
                cursosCadastrados[j].descricao);
        fprintf(arqRelatorio, "Carga Horária: %d\n",
                cursosCadastrados[j].cargaHoraria);
        fprintf(arqRelatorio, "Preço: %.2f\n\n",
                (cursosCadastrados)[j].precoCurso);
      }
    }
  }
  fclose(arqRelatorio);
}

void listarCursosPorAluno(Matricula *matriculasCadastradas,
                          Curso *cursosCadastrados, int qtd_matriculas,
                          int qtd_curso) {
  double id;
  printf("Digite o cpf do aluno que deseja consultar: ");
  scanf("%lf", &id);
  int encontrouAluno = -1;
  for (int i = 0; i < qtd_matriculas; i++) {
    if ((matriculasCadastradas)[i].cpfAluno == id) {
      encontrouAluno = 1;
      break;
    }
  }

  if (encontrouAluno == -1) {
    printf("Aluno não matriculado!\n\n");
    return;
  }

  int *codigoCursosAluno = malloc(sizeof(Curso) * qtd_curso);
  int j = 0;

  for (int i = 0; i < qtd_matriculas; i++) {
    if ((matriculasCadastradas)[i].cpfAluno == id) {
      codigoCursosAluno[j] = (matriculasCadastradas)[i].codigoCurso;
      j++;
    }
  }
  char nomeArquivo[256];
  printf("Digite o nome do arquivo para salvar o relatório (digite um nome de "
         "arquivo já existente caso queira sobrescrevê-lo: ");
  scanf("%s", nomeArquivo);
  strcat(nomeArquivo, ".txt");
  char nVet[50];
  FILE *arq = fopen(nomeArquivo, "w");
  for (int i = 0; i < j; i++) {
    for (int j = 0; j < qtd_curso; j++) {
      if ((cursosCadastrados)[j].codigo == codigoCursosAluno[i]) {
        printf("=========================================\n");
        printf("\nNome curso: %s\n", (cursosCadastrados)[j].nomeCurso);
        printf("Codigo: %d\n", (cursosCadastrados)[j].codigo);
        printf("Carga Horaria (em horas): %d\n",
               (cursosCadastrados)[j].cargaHoraria);
        printf("Descrição: %s\n", (cursosCadastrados)[j].descricao);
        printf("Preço: %.2f\n\n", (cursosCadastrados)[j].precoCurso);

        fputs("=========================================\n", arq);
        fputs("\nNome curso: ", arq);
        fputs((cursosCadastrados)[j].nomeCurso, arq);
        fputs("\nCódigo: ", arq);
        fprintf(arq, "%d", cursosCadastrados[i].codigo);
        fputs("\nCarga Horária: ", arq);
        fprintf(arq, "%d", cursosCadastrados[i].cargaHoraria);
        fputs("\nDescrição: ", arq);
        fputs((cursosCadastrados)[j].descricao, arq);
        fputs("\nPreço: ", arq);
        fprintf(arq, "%.2f", cursosCadastrados[i].precoCurso);
        fputs("\n\n", arq);
      }
    }
  }
  fclose(arq);
  free(codigoCursosAluno);
}

void subMenuRelatorio(Curso **cursosCadastrados, Aluno **alunosCadastrados,
                      Matricula **matriculasCadastradas, int qtd_alunos,
                      int qtd_cursos, int qtd_matriculas) {
  system(CLEAR);
  int opt;
  printf("=========== Submenu de Relatórios =========== \n");
  printf("\t1. Todos alunos de determinado curso\n");
  printf("\t2. Todos os cursos de determinada data\n");
  printf("\t3. Todos os cursos realizados por determinado aluno\n");
  printf("\t4. Menu principal\n");
  printf("-> ");
  scanf("%d", &opt);
  switch (opt) {
  case 1:
    listarAlunosPorCurso(*cursosCadastrados, qtd_cursos, *alunosCadastrados,
                         qtd_alunos, *matriculasCadastradas, qtd_matriculas);

    break;
  case 2:
    listarCursoPorData(*matriculasCadastradas, *cursosCadastrados,
                       qtd_matriculas, qtd_cursos);
    break;
  case 3:
    listarCursosPorAluno(*matriculasCadastradas, *cursosCadastrados,
                         qtd_matriculas, qtd_cursos);
    break;
  case 4:
    system(CLEAR);
    return;
    break;
  default:
    printf("\nVocê digitou um número inválido\n");
    break;
  }
}

////// Leitura de Arquivos ///////
void lerArqQuantidades(int *qtd_alunos, int *qtd_cursos, int *qtd_matriculas,
                       FILE *arqQuantidades) {
  arqQuantidades = fopen("arqQuantidades.bin", "rb+");

  if (arqQuantidades == NULL) {
    printf("O arquivo 'arqQuantidades.bin' ainda não existe, mas será criado "
           "ao final do programa!\n\n");
  } else {
    fread(qtd_alunos, sizeof(int), 1, arqQuantidades);
    fread(qtd_cursos, sizeof(int), 1, arqQuantidades);
    fread(qtd_matriculas, sizeof(int), 1, arqQuantidades);
    fclose(arqQuantidades);
  }
}

void lerArqAlunos(Aluno **alunosCadastrados, int *qtd_alunos, FILE *arqAlunos) {
  arqAlunos = fopen("arqAlunos.bin", "rb+");
  if (arqAlunos == NULL) {
    printf("O arquivo 'arqAlunos.bin' ainda não existe, mas será criado ao "
           "final do programa!\n\n");
    *qtd_alunos = 0;
  } else {
    *alunosCadastrados = malloc(sizeof(Aluno) * (*qtd_alunos));
    fread(*alunosCadastrados, sizeof(Aluno), *qtd_alunos, arqAlunos);
    fclose(arqAlunos);
  }
}

void lerArqCursos(Curso **cursosCadastrados, int *qtd_cursos, FILE *arqCursos) {
  arqCursos = fopen("arqCursos.bin", "rb+");
  if (arqCursos == NULL) {
    printf("O arquivo 'arqCursos.bin' ainda não existe, mas será criado ao "
           "final do programa!\n\n");
    *qtd_cursos = 0;
  } else {
    *cursosCadastrados = malloc(sizeof(Curso) * (*qtd_cursos));
    fread(*cursosCadastrados, sizeof(Curso), *qtd_cursos, arqCursos);
    fclose(arqCursos);
  }
}

void lerArqMatriculas(Matricula **matriculasCadastradas, int *qtd_matriculas,
                      FILE *arqMatriculas) {
  arqMatriculas = fopen("arqMatriculas.bin", "rb+");
  if (arqMatriculas == NULL) {
    printf("O arquivo 'arqMatriculas.bin' ainda não existe, mas será criado ao "
           "final do programa!\n\n");
    *qtd_matriculas = 0;
  } else {
    *matriculasCadastradas = malloc(sizeof(Matricula) * (*qtd_matriculas));
    fread(*matriculasCadastradas, sizeof(Matricula), *qtd_matriculas,
          arqMatriculas);
    fclose(arqMatriculas);
  }
}

////// Escrita nos arquivos //////
void salvarQuantidades(int qtd_alunos, int qtd_cursos, int qtd_matriculas,
                       FILE *arqQuantidades) {
  arqQuantidades = fopen("arqQuantidades.bin", "wb+");
  if (arqQuantidades == NULL) {
    printf("Erro ao salvar os dados das quantidades.\n\n");
    return;
  } else {
    fwrite(&qtd_alunos, sizeof(int), 1, arqQuantidades);
    fwrite(&qtd_cursos, sizeof(int), 1, arqQuantidades);
    fwrite(&qtd_matriculas, sizeof(int), 1, arqQuantidades);
  }
  fclose(arqQuantidades);
}

void salvarAlunos(Aluno *alunosCadastrados, int qtd_alunos, FILE *arqAlunos) {
  arqAlunos = fopen("arqAlunos.bin", "wb+");
  if (arqAlunos == NULL) {
    printf("Erro ao salvar os dados dos alunos.\n\n");
    return;
  } else {
    fwrite(alunosCadastrados, sizeof(Aluno), qtd_alunos, arqAlunos);
  }
  fclose(arqAlunos);
}

void salvarCursos(Curso *cursosCadastrados, int qtd_cursos, FILE *arqCursos) {
  arqCursos = fopen("arqCursos.bin", "wb+");
  if (arqCursos == NULL) {
    printf("Erro ao salvar os dados dos cursos\n\n");
    return;
  } else {
    fwrite(cursosCadastrados, sizeof(Curso), qtd_cursos, arqCursos);
  }
  fclose(arqCursos);
}

void salvarMatriculas(Matricula *matriculasCadastradas, int qtd_matriculas,
                      FILE *arqMatriculas) {
  arqMatriculas = fopen("arqMatriculas.bin", "wb+");
  if (arqMatriculas == NULL) {
    printf("Erro ao salvar os dados das matrículas\n\n");
    return;
  } else {
    fwrite(matriculasCadastradas, sizeof(Matricula), qtd_matriculas,
           arqMatriculas);
  }
  fclose(arqMatriculas);
}

int main() {
  system(CLEAR);
  setlocale(LC_ALL, "Portuguese");
  int i;
  int qtd_alunos = 0, qtd_cursos = 0, qtd_matriculas = 0;
  Aluno *alunosCadastrados = NULL;
  Curso *cursosCadastrados = NULL;
  Matricula *matriculasCadastradas = NULL;
  FILE *arqQuantidades, *arqAlunos, *arqCursos, *arqMatriculas;

  // Leitura dos arquivos
  lerArqQuantidades(&qtd_alunos, &qtd_cursos, &qtd_matriculas, arqQuantidades);
  lerArqAlunos(&alunosCadastrados, &qtd_alunos, arqAlunos);
  lerArqCursos(&cursosCadastrados, &qtd_cursos, arqCursos);
  lerArqMatriculas(&matriculasCadastradas, &qtd_matriculas, arqMatriculas);

  int opt, opcSubmenu;

  char submenu[15];
  do {
    menu();
    scanf("%d", &opt);
    switch (opt) {
    case 1:
      system(CLEAR);
      subMenuAlunos(&alunosCadastrados, &qtd_alunos);
      break;
    case 2:
      system(CLEAR);
      subMenuCursos(&cursosCadastrados, &qtd_cursos);
      break;
    case 3:
      system(CLEAR);
      subMenuMatriculas(&matriculasCadastradas, &qtd_matriculas,
                        &alunosCadastrados, qtd_alunos, &cursosCadastrados,
                        qtd_cursos);
      break;
    case 4:
      // submenu de relatórios
      system(CLEAR);
      subMenuRelatorio(&cursosCadastrados, &alunosCadastrados,
                       &matriculasCadastradas, qtd_alunos, qtd_cursos,
                       qtd_matriculas);
      break;
    case 5:
      printf("\nEncerrando o programa...\n");
      salvarQuantidades(qtd_alunos, qtd_cursos, qtd_matriculas, arqQuantidades);
      salvarAlunos(alunosCadastrados, qtd_alunos, arqAlunos);
      salvarCursos(cursosCadastrados, qtd_cursos, arqCursos);
      salvarMatriculas(matriculasCadastradas, qtd_matriculas, arqMatriculas);
      break;
    default:
      printf("\nVocê digitou um número inválido\n");
      printf("\nEncerrando o programa...\n");
      salvarQuantidades(qtd_alunos, qtd_cursos, qtd_matriculas, arqQuantidades);
      salvarAlunos(alunosCadastrados, qtd_alunos, arqAlunos);
      salvarCursos(cursosCadastrados, qtd_cursos, arqCursos);
      salvarMatriculas(matriculasCadastradas, qtd_matriculas, arqMatriculas);
      break;
    }
  } while (opt >= 1 && opt < 5);

  free(alunosCadastrados);
  free(cursosCadastrados);
  free(matriculasCadastradas);
}
