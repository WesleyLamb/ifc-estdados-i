---
marp: true
theme: uncover
class: invert
---

# Shell Sort e Radix Sort
Alunos: Valdir Rugiski, Virgílio Luigi e Wesley Lamb

---

## Shell Sort

- Criado por Donald Shell em 1959;
- Foi utilizado no Kernel do Linux devido seu baixo uso de recursos computacionais.

---

### Características

- É um algoritmo de ordenação que melhora o desempenho do Insertion Sort;
- A ideia é ordenar elementos distantes um do outro com um insertion sort e reduzir essa distância a cada iteração;
- A distância entre os elementos é chamada de gap;
- O algoritmo termina quando o gap é igual a 1.

---

### O algoritmo

```c
void shellSort(int *vet, int size) {
    int i, j, value;

    int h = 1;
    while(h < size) {
        h = 3*h+1;
    }
    while (h > 0) {
        for(i = h; i < size; i++) {
            value = vet[i];
            j = i;
            while (j > h-1 && value <= vet[j - h]) {
                vet[j] = vet[j - h];
                j = j - h;
            }
            vet[j] = value;
        }
        h = h/3;
    }
}
```

---

### Análise de complexidade

- O pior caso do Shell Sort é O(n²)
- O melhor caso é O(n log n)

---

## Radix Sort

- Há registros de seu uso desde 1887, por Herman Hollerith (sim, o mesmo dos extratos bancários);
- Foi muito utilizado para ordenação de cartões perfurados;
- É possível utilizar na vida real tranquilamente para qualquer sequência.

---

## Características

- Pode ser implementado começando pelo dígito de menor significância (LSD) ou pelo dígito de maior significância (MSD);
- Pode trabalhar em qualquer base (base 2, base 4, base 10, etc);
- Não usa comparação.

---

## Os algoritmos
---

```c
void radixSortL(int* vet, int size) {
    int i, j, k;
    int B[size];
    int maior = vet[0];
    int exp = 1;

    for (i = 0; i < size; i++) {
        if (vet[i] > maior)
    	    maior = vet[i];
    }

    while (maior/exp > 0) {
        int bucket[10] = { 0 };
        for (i = 0; i < size; i++)
    	    bucket[vet[i] / exp % 10]++;
        for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
        for (i = size - 1; i >= 0; i--)
    	    B[--bucket[vet[i] / exp % 10]] = vet[i];
        for (i = 0; i < size; i++)
    	    vet[i] = B[i];
        exp *= 10;
    }
}
```

---

```c
void radixSortM(int* vet, int size) {
    int i, j, k, m, n, p, q, t;
    int* cnt = (int*)malloc(sizeof(int)*256);
    int* tmp = (int*)malloc(sizeof(int)*size);

    for (k = 31; k >= 0; k -= 8) {
        for (i = 0; i < 256; i++) {
            cnt[i] = 0;
        }
        for (i = 0; i < size; i++) {
            cnt[(vet[i] >> k) & 0xff]++;
        }
        for (i = 1; i < 256; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (i = size - 1; i >= 0; i--) {
            j = (vet[i] >> k) & 0xff;
            tmp[--cnt[j]] = vet[i];
        }
        for (i = 0; i < size; i++) {
            vet[i] = tmp[i];
        }
    }

    free(cnt);
    free(tmp);
}
```