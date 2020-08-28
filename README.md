# O problema do Carteiro Chinês

[![Build Status](https://travis-ci.org/gafeol/chinese-postman.svg?branch=master)](https://travis-ci.org/gafeol/chinese-postman)

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

Após isso, basta rodar `make -C test` que todos os tetes serão executados.

## Problemas comuns

**Se durante a compilação automática do arquivo tex você receber o erro "compilation failed, file "bla.tex" not found:**

Pare a compilação automática `\lk`, limpe os arquivos auxiliares de compilação `\lc`, reinicie a compilação automática `\ll`.

Se isso não funcionar, feche tudo, e dê um `make` na pasta principal.

## Referências

https://github.com/dilsonpereira/Minimum-Cost-Perfect-Matching

https://github.com/dilsonpereira/chinese-postman-problem
