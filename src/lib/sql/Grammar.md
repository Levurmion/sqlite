# SQL Grammar

**Queries**
| non-terminal | description |
|--------------|-------------|
|`<select_query>`| SQL `SELECT` query|
|`<create_query>`| SQL `CREATE` query|

**Clauses**

| non-terminal | description |
|--------------|-------------|
|`<select_clause>`| The column selection clause preceeded by `SELECT`|
|`<from_clause>`| The table selection clause preceeded by `FROM`|
|`<where_clause>`| The conditional selection clause preceeded by `WHERE`|

**Lists**
| non-terminal | description |
|--------------|-------------|
|`<column_list>`| A list of column identifiers |


## Rules

### <select_query> grammar

```
<select_query> ::= <select_clause> <from_clause> [<where_clause>]

<select_clause> ::= "SELECT"<column_list>
<column_list> ::= `id`<column_list> | e

<from_clause> ::= "FROM"`id`
```
