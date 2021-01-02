# O problema do Carteiro Chinês

[![Build Status](https://travis-ci.org/gafeol/chinese-postman.svg?branch=master)](https://travis-ci.org/gafeol/chinese-postman)
[![codecov](https://codecov.io/gh/gafeol/chinese-postman/branch/master/graph/badge.svg)](https://codecov.io/gh/gafeol/chinese-postman)

Trabalho de Conclusão de Curso desenvolvido por Gabriel Fernandes de Oliveira no ano de 2020, com a orientação do Prof. Carlos Eduardo Ferreira.

## Compilando o documento

Para conseguir compilar o latex, é necessário instalar os seguintes pacotes:

```bash
texlive-latex-base
texlive-lang-portuguese
texlive-science
texlive-bibtex-extra
biber
```

Depois de instalados, basta rodar `make` que o pdf será compilado, e os arquivos auxiliares serão deletados.

## Organização

### Arquivos LaTeX

Os arquivos LaTeX estão todos dispostos na pasta `tex`.

O documento principal é o main.tex, que tem todas as importações de pacotes e de arquivos auxiliares.

- Em **euler.tex** você encontra a seção que trata sobre caminhos eulerianos.
- Em **pcc.tex** você encontra o texto principal, sobre o problema do carteiro chinês.
- Em **prb.tex** você encontra exercícios e problemas resolvidos relacionados aos temas tratados no trabalho.
- Finalmente em **ref.bib** estão as referências bibliográficas da monografia.

### Código

Os arquivos de código estão dispostos na pasta `code/`, e seus respectivos testes se encontram na pasta `test/`;

### Testes de Código

Os testes foram desenvolvidos usando a ferramenta "googletest" da Google.

Para entender os usos básicos e motivações de se usar o googletest, segue essa [apresentação](https://docs.google.com/presentation/d/1miS-qttABKfkIT9TG_HU6Kn3FrxZ9VNHD7nHIL4_3wE/present#slide=id.i0).

Para realizar os testes, certifique-se de que a pasta `test/gtest` foi devidamente clonada.
Se a mesma estiver vazia, basta cloná-la usando o comando:

```bash
git clone git@github.com:google/googletest.git test/gtest
```

Após isso, basta rodar `make -C test` que todos os testes serão executados.

Se desejar rodar apenas um conjunto específico de testes, inclua o nome do conjunto desejado após o `make`, por exemplo:

```bash
# Para rodar os testes de grafos nao direcionados
make grafo -C test/
make graph -C test/

# Para todar os testes de emparelhamento
make matching -C test/
```

#### Cobertura de testes

Para checar a cobertura de testes manualmente, primeiramente configure a variável de ambiente `CODECOV_TOKEN`.
Minha sugestão é adicioná-la a um arquivo `secret`, ignorado pelo github, no formato:

```bash
export CODECOV_TOKEN=aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa
```

Após isso basta rodar `source secret`.

Tendo definida tal variável, pode-se testar manualmente a cobertura dos testes rodando:

```bash
make -C test/
bash <(curl -s https://codecov.io/bash) -t $CODECOV_TOKEN
```

Se o comando rodou como esperado, a última linha do mesmo deverá ser da forma:

```bash
[...]
-> View reports at https://codecov.io/github/gafeol/chinese-postman/commit/f81abd57f0e0238709a4000cd179163b32124ddb
```

Acessando o link dado pode-se observar o resultado de cobertura dos testes atualmente adicionados ao projeto.
Este teste de cobertura nos oferece informações muito importantes, como por exemplo: quais linhas de código nunca foram executadas nos testes.

## Referências

Todas as referências bibliográficas são apresentadas na monografia, e são organizadas usando Bibtex no arquivo `tex/ref.bib`.

A implementação do Emparelhamento Perfeito Mínimo foi baseada na implementação de [Adilson Pereira](https://github.com/dilsonpereira/Minimum-Cost-Perfect-Matching) e adaptada para esse projeto em um [fork próprio](https://github.com/gafeol/Minimum-Cost-Perfect-Matching).

A implementação do algoritmo de Chu-Liu para encontrar a arborescência geradora mínima em um digrafo foi baseada na implementação do time ["el-vasito"](https://github.com/mhunicken/icpc-team-notebook-el-vasito) disponibilizada em seu caderno de referência para a ICPC.
