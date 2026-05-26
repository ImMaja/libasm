# libasm

Projet d'assembleur x86-64 dont le but est de recreer plusieurs fonctions
standard de la libc en NASM, syntaxe Intel.

La bibliotheque generee s'appelle `libasm.a`.

## Objectif

Le projet permet de se familiariser avec :

- les registres x86-64 ;
- la convention d'appel 64 bits ;
- la manipulation directe de la memoire ;
- la creation d'une bibliotheque statique ;
- les appels systeme et la gestion de `errno`.

## Fonctions obligatoires

Le sujet demande de reimplementer les fonctions suivantes en assembleur :

- `ft_strlen`
- `ft_strcpy`
- `ft_strcmp`
- `ft_write`
- `ft_read`
- `ft_strdup`

## Fonctions bonus

Le sujet propose aussi les fonctions bonus suivantes :

- `ft_atoi_base`
- `ft_list_push_front`
- `ft_list_size`
- `ft_list_sort`
- `ft_list_remove_if`

## Compilation

Compiler la bibliotheque :

```sh
make
```

Compiler le programme de test :

```sh
make test
```

Lancer les tests :

```sh
./test
```

Nettoyer les fichiers objets :

```sh
make clean
```

Nettoyer tous les fichiers generes :

```sh
make fclean
```

Recompiler depuis zero :

```sh
make re
```

## Structure

```text
.
├── Makefile
├── README.md
├── en.subject.pdf
├── srcs/
│   ├── ft_strlen.s
│   └── ft_strcpy.s
└── tests/
    └── main.c
```

## Notes

- Le code assembleur doit etre compile avec `nasm`.
- Le projet utilise la syntaxe Intel.
- Le flag `-no-pie` est interdit par le sujet.
- Les fonctions doivent respecter la convention d'appel x86-64.
- Les fonctions utilisant des syscalls devront gerer les erreurs et mettre `errno`
  correctement.
