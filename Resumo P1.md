# 1. Tradução de Linguagens de Programação

## 1.3 Estrutura de um tradutor:
1. **Análise Léxica**: identificar a sequência de caractéres que constituem os tokens + construir a tabela de símbolos. Encontra erros léxicos. O input é analisado como uma **Linguagem Regular.**
2. **Análise Sintática**: Verificar se a estrutura gramatical do programa está correta e produção da AST (árvore de sintaxe abstrata), que elimina redundâncias e elementos desnecessários (comentários). Encontra erros sintáticos. O input é analisado como uma **Linguagem Livre de Contexto.**
3. **Análise Semântica**: Verifica se as estruturas sintáticas fazem sentido.
4. **Geração de código intermediário**: Utiliza a estrutura produzida pelo parser para gerar código intermediário que pode ser otimizado posteriormente. Não especifica detalhes, tipo quais registradores fazem o quê ou quais endereços de memória usar, somente a lógica.
5. **Otimização de código**: Otimizar o código intermediário em velocidade e espaço de memória.
6. **Geração de código objeto**: Produção de código que pode ser executado, por exemplo, para linguagem de máquina ou assembler.

## 2. Análise Léxica
_Fazer a leitura do programa fonte e traduzir para uma sequência de símbolos léxicos (tokens)._

- **Símbolos léxicos:** são as *palavras reservadas*, *identificadores*, *constantes* e *operadores*.
- **Por que usar um analisador léxico separado do sintático?**
	1. Simplificação do projeto do compilador
	2. tokens descritos com Expressões Regulares são mais simples do que com uma Linguagem Livre de contexto (que o analisador sintático usa), além de serem mais eficientes e compactos.

#### Tabela de símbolos
*Estrutura de dados usada para armazenar os nomes definidos no fonte: identificadores de variáveis, funções, parâmetros...*
- A tabela armazena também tipo, escopo, limites de vetores, número de parâmetros. 
- Comumente se usa Hash para a estrutura.

## 3. Análise Sintática
*Verificar se as construções usadas no programa estão gramaticalmente corretas. Utiliza-se geralmente uma Gramática Livre de Contexto. Produz uma AST (árvore de sintaxe abstrata ou árvore de derivação).*

#### Estratégias de análise sintática
1. **Top-Down (expansão):** Constrói a árvore a cada passo, uma produção se torna um terminal. 
2. **Bottom-Up (redução):** Constrói a árvore a partir dos tokens até o símbolo inicial.

#### Gramáticas Livres de Contexto (GLCs)
Uma **Gramática Livre de Contexto (GLC)** é definida como `G = (N, T, P, S)`, onde:

- `N`: Conjunto de símbolos **Não-terminais** (variáveis).
- `T`: Conjunto de símbolos **Terminais** (o alfabeto da linguagem).
- `P`: Conjunto de **Regras de Produção** no formato `A -> α`, onde `A` é um não-terminal (`A ∈ N`) e `α` é uma sequência de terminais e/ou não-terminais (`α ∈ (N U T)*`).
- `S`: Símbolo inicial da gramática.

##### 1. Eliminação de Produções Vazias (ε-produções)

**Objetivo:** Remover todas as produções da forma `A -> ε` (onde `ε` é a cadeia vazia), exceto, se necessário, para o símbolo inicial.

**Processo:**

1. **Identificar Não-Terminais Anuláveis:** Encontre todos os não-terminais que podem derivar a cadeia vazia (`ε`). Um não-terminal `A` é anulável se:
    
    - Existe uma produção `A -> ε`.
    - Existe uma produção `A -> B₁B₂...Bₖ` onde todos os `Bᵢ` são anuláveis.
    
2. **Criar Novas Produções:** Para cada produção `A -> α` que contenha um ou mais não-terminais anuláveis, adicione novas produções que representem todas as combinações possíveis da ausência desses não-terminais.
    
    - **Exemplo:** Se `B` é anulável e existe a regra `A -> xBy`, adicione uma nova regra `A -> xy`. Se a regra fosse `A -> B₁B₂` com ambos anuláveis, você adicionaria `A -> B₁`, `A -> B₂` e `A -> ε` (que depois será tratada).
    
3. **Remover as ε-produções:** Apague todas as regras da forma `A -> ε`.
    
4. **Caso Especial do Símbolo Inicial (S):** Se `S` for um não-terminal anulável, a linguagem gerada pela gramática contém a cadeia vazia. Para preservar isso, adicione um novo símbolo inicial `S'` e as produções:
    
    - `S' -> S | ε`
    - `S` mantém todas as suas produções originais (exceto a produção `S -> ε`, se houver).

##### 2. Eliminação de Recursividade à Esquerda

**Objetivo:** Remover produções que causam um loop infinito em analisadores sintáticos descendentes (top-down), como `A -> Aα`.

**Processo (para recursão direta):**

1. **Identificar a Recursão:** Para um não-terminal `A`, separe suas produções em dois grupos:
    
    - As que começam com `A` (recursivas): `A -> Aα₁ | Aα₂ | ...`
    - As que **não** começam com `A` (não recursivas): `A -> β₁ | β₂ | ...`
    
2. **Reescrever as Regras:** Substitua o conjunto de regras de `A` por um novo conjunto, introduzindo um novo não-terminal (ex: `A'`):
    
    - `A -> β₁A' | β₂A' | ...`
    - `A' -> α₁A' | α₂A' | ... | ε`

**Intuição:** A regra antiga `A -> β₁` inicia a derivação. O novo símbolo `A'` é responsável por "empilhar" opcionalmente e repetidamente as partes que vinham após a recursão (`αᵢ`).

##### 3. Fatoração da Gramática

**Objetivo:** Eliminar a incerteza para analisadores preditivos (como o LL(1)), que precisam saber qual regra escolher olhando apenas um símbolo à frente (lookahead). Isso é feito eliminando prefixos comuns em produções de um mesmo não-terminal.

**Processo:**
1. **Identificar o Prefixo Comum:** Para um não-terminal `A`, encontre um conjunto de produções que começam com o mesmo prefixo `α`.
    
    - Formato: `A -> αβ₁ | αβ₂ | ... | αγ`
    
2. **Fatorar o Prefixo:** Crie um novo não-terminal (ex: `A'`) para lidar com a parte que varia _após_ o prefixo comum.
    
    - A regra original de `A` é substituída por: `A -> αA'`
    - As novas regras para `A'` são criadas com o restante das produções originais: `A' -> β₁ | β₂ | ... | γ`

**Exemplo:**
- **Original:** `S -> iEtS | iEtSeS | a`
- **Prefixo comum:** `iEtS`
- **Fatorada:**
    
    - `S -> iEtSS' | a`
    - `S' -> eS | ε`


### Análise Descendente (Top-Down)
#### Recursiva com Retrocesso
*Expande sempre o Não-terminal mais à esquerda. Se o token não define sem dúvidas a produção a ser usada, todas são testadas até alguma dar certo ou falhar.*
- É ineficiente e não usado geralmente

#### Tabular preditiva
*Utilizam uma pilha explícita*

![[Preditivo Tabular]]

- Definição da tabela de análise:
	1. Eliminar recursões à esquerda.
	2. Encontrar o **first** e **follow**  cada produção
	3. Preencher a tabela de análise

##### First($A$)
_Conjunto de terminais que iniciam A ou derivações de A_
EX.:
G = {
	E-> TE'
	E'-> $\lor$TE | $\epsilon$ 
	T-> FT'
	T'-> &FT' | $\epsilon$
	F-> $¬$ | $id$
}
First(E) = { $¬$ , $id$ }
First(E') = { $\lor$ , $\epsilon$ }
First(T) = { $¬$ , $id$ }
First(T') = { & , $\epsilon$ }
First(F) = { $¬$ , $id$ }
##### Follow($A$)
_Conjunto de terminais que podem aparecer à direita de $A$ MENOS $\epsilon$_
Follow(E) = { $\$$ }
Follow(E') = { $\$$ }
Follow(T) = { $\$$, $\lor$ }
Follow(T') = { $\$$, $\lor$,  }
Follow(F) = { $\$$, $\lor$, $\&$ }

##### Tabela preditiva $M[A,\alpha]$ com First($\alpha$) e Follow($\alpha$)
Para gerar a tabela preditiva, segue-se o algoritmo:
1. Para cada produção de G do tipo $A\rightarrow \alpha$:
	1. Para cada terminal de First($\alpha$), $M[A,\alpha]$ = $A\rightarrow \alpha$
	2. Se First($\alpha$) contém $\epsilon$,  $M[A,\alpha]$ = $A\rightarrow \beta$ para cada $\beta$ em Follow($\alpha$)

|     | $id$     | $\lor$          | $\&$      | $¬$     | $\$$            |
| --- | -------- | --------------- | --------- | ------- | --------------- |
| E   | E-> TE'  |                 |           | E-> TE' |                 |
| E'  |          | E'-> $\lor$TE   |           |         | E'-> $\epsilon$ |
| T   | T-> FT'  |                 |           | T-> FT' |                 |
| T'  |          | T'-> $\epsilon$ | T'-> &FT' |         | T'-> $\epsilon$ |
| F   | F-> $id$ |                 |           | F-> $¬$ |                 |


### Análise Redutiva (Bottom-Up)
*Constrói a árvore a partir das folhas, produzindo uma derivação mais à direita*

### Analisadores LR(k)
*Left to right with Rightmost derivation*

![[LR(k)]]

### Construção de Analisadores SLR

##### 1. Itens LR(0)
- São Produções com um ponto do lado direito, simbolizando até onde a Produção já foi analisada:
	- `A -> XYZ` 
		origina os seguintes itens:
	- `A -> . X Y Z`
	- `A -> X . Y Z`
	- `A -> X Y . Z`
	- `A -> X Y Z .`

##### 2. Cálculo da Função closure(I)
1. Todo item em I pertence a $closure(I)$
2. Se $A \rightarrow \alpha . X \beta$ está no conjunto $closure(I)$, as produções $X \rightarrow .  \gamma$ são adicionadas ao conjunto closure(I).
##### 3. Cálculo da Função goto(I, X)
1. Coletar as produções com ponto no lado esquerdo de X.
2. Passar o ponto para o lado direito de X.
3. Obter o closure(I) desse conjunto.
##### 4. Algoritmo para obter Conjunto C de itens LR(0)
1. Inicializar $C = \{ I_0 = closure(\{ S' \rightarrow .S \}) \}$
2. For $I \in C$
	For $\alpha \in G$ (símbolos da gramática)
		$C + goto(I, \alpha)$
3. Repetir o passo 2 até todos os conjuntos estarem em C
##### 5. Construção da tabela de análise SLR
Seja $C = \{ I_0, I_1, ..., I_n \}$ o conjunto C e $0, 1, ..., n$ os estados do analisador. Para cada linha em [0,n], 
1. Se $goto(I,a) = I_j$, então $AÇÃO[i, a] = empilha\ j$.
2. Se $A \rightarrow \alpha . \in I_i$, para todo $a \in follow(A)$, $AÇÃO[i, a] = reduz\ n$, sendo $n$ o número da produção $A \rightarrow \alpha$  
3. Se $S' \rightarrow S \in I_i$, $AÇÃO[i, \$] = ACEITA$
4. Se $goto(I_i, A) = I_j, TRANSIÇÃO(i, A) = j$ 

##### 6. Uso da tabela de análise
Para cada consulta na tabela, com $E_m$ sendo o estado no topo da pilha, $AÇÃO[E_m, a_i]$
- Empilha $e_x$ : Empilha $a_i\ e_x$
- Reduz $r_n$: Reduz n, onde n é o número da produção $A \rightarrow \beta$. Causa o desempilhamento de $2r$ símbolos, sendo $r = |\beta|$, e o empilhamento de $AE_y$, sendo $E_y$ o resultado da consulta na tabela de $TRANSIÇÃO[E_m, A]$. OBS.: $E_m$ é após a redução da pilha.  
- Aceita
