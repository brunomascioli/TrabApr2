# TrabApr2

## Tema 1: Gerenciamento de cursos

Uma escola de cursos online de rápida duração deseja um sistema para gerenciar os dados de cada aluno e de cada curso realizado por um aluno. Os dados a serem armazenados sobre cada uma dessas entidades são apresentados a seguir:

- Alunos = (CPF, Nome, Data de Nascimento, Sexo, E-mails, Telefones)
- Cursos = (Código, Descrição, Carga horária, Preço)  
- Matrícula = (CPF Aluno, Código curso, Data de início, Data de término, Desconto)

**Atenção:** os atributos grifados são chaves e você **NÃO** deve permitir a inclusão de mais de um cadastro com os mesmos valores para os atributos chaves.

Utilizando os conhecimentos aprendidos sobre Vetores, Strings, Registros e Funções desenvolva um programa em C que apresente o seguinte menu de opções para o usuário e implemente cada operação usando função. Escolha a estrutura de dados mais apropriada para armazenar os dados de cada entidade descrita anteriormente.

## Menu Principal:
1. Submenu de Alunos
2. Submenu de Cursos
3. Submenu de Matrícula
4. Submenu Relatórios
5. Sair

Cada Submenu deverá oferecer as opções: Listar todos, Listar um, Incluir (sem repetição), Alterar e Excluir (após confirmação dos dados) um elemento do conjunto. O Submenu Relatórios deverá ter uma opção para cada um dos relatórios solicitados abaixo.

## Relatórios:
a) Mostrar o nome do curso, o CPF, o nome e os e-mails de todos os alunos que cursaram determinado curso cujo o código será fornecido pelo usuário;
b) Mostrar os dados de todos os cursos oferecidos entre as datas X e Y, onde as datas devem ser fornecidas pelo usuário;
c) Mostrar os dados de todos os cursos realizados por determinado aluno, cujo CPF será fornecido pelo usuário.

A aplicação deverá utilizar Arquivos para a persistência dos dados. Em outras palavras, cada registro de Aluno, Curso e Matrícula deverá ser armazenado em um arquivo binário específico, que conterá apenas registros daquele mesmo tipo de entidade. Para os relatórios você deverá usar arquivos textos. Utilize estruturas dinâmicas como vetores e registros alocados dinamicamente para o armazenamento temporário dos dados (ou seja, antes de serem gravados em arquivos).
