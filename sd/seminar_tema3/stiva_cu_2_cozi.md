# Implementarea unei Stive folosind Două Cozi

### Varianta 1: Push în O(n), Pop în O(1)
Push:
1. Se adaugă elementul nou în coada 2
2. Se mută toate elementele din coada 1 în coada 2
3. Se face swap între cozi

Pop:
1. Se returnează primul element din coada 1

### Varianta 2: Push în O(1), Pop în O(n)
Push:
1. Se adaugă elementul nou în coada 1

Pop:
1. Se mută toate elementele din coada 1 în coada 2, cu excepția ultimului element
2. Se returnează ultimul element din coada 1
3. Se face swap între cozi