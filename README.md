# Minishell

42 Common Core project - Team of two.

**Authors:** [hrandria](https://github.com/Hera-r) and mle-bras

---

## Description

A simplified shell inspired by bash, handling:

- Command execution with absolute and relative paths
- Pipes (`|`) and redirections (`>`, `>>`, `<`, `<<`)
- Environment variable expansion (`$VAR`, `$?`)
- Single and double quote handling
- Signal management (Ctrl+C, Ctrl+D, Ctrl+\\)
- Builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

## Build

```
make
```

## Usage

```
./minishell
```

## Clean

```
make clean    # remove object files
make fclean   # remove object files and binary
make re       # full rebuild
```

---

# Minishell (VF)

Projet 42 Common Core - Groupe de deux.

**Auteurs :** [hrandria](https://github.com/Hera-r) et mle-bras

---

## Description

Un shell simplifie inspire de bash, gerant :

- Execution de commandes avec chemins absolus et relatifs
- Pipes (`|`) et redirections (`>`, `>>`, `<`, `<<`)
- Expansion de variables d'environnement (`$VAR`, `$?`)
- Gestion des guillemets simples et doubles
- Gestion des signaux (Ctrl+C, Ctrl+D, Ctrl+\\)
- Builtins : `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

## Compilation

```
make
```

## Utilisation

```
./minishell
```

## Nettoyage

```
make clean    # supprime les fichiers objets
make fclean   # supprime les fichiers objets et le binaire
make re       # recompilation complete
```
