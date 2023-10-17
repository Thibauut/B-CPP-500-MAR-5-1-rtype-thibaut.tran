- Protocole TCP

  * NAME = “Nom du joueur ciblé”

  * PLAYER_ID = “ID du joueur ciblé”
  
  * LEVEL = “Niveau du joueur ciblé”
 
  * ROOM_ID = “ID de la room ciblée”

  * NB_SLOT = “Nombre de slot max de la room (1 - 10)”
  
→ LE CLIENT

← LE SERVER

  Une requête se fait comme ceci :
  COMMANDE<SP>“arg1"<SP> “arg2"<SP> “arg3 “
  
  En exemple concret:
  CREATE_ROOM “12dffhdj234djdh” “4” “room test”
  
* Requests:

  → LOGIN NAME
  
  ← LOGIN PLAYER_ID
  
  → GET_PLAYER_INFO PLAYER_ID
  
  ← GET_PLAYER_INFO NAME LEVEL
  
  → DISCONNECT PLAYER_ID
  
  ← DISCONNECT OK/KO
  
  → CREATE_ROOM PLAYER_ID NB_SLOT NAME
  
  ← CREATE_ROOM OK/KO
  
  → JOIN_ROOM ROOM_ID PLAYER_ID
  
  ← JOIN_ROOM OK/KO
  
  → READY PLAYER_ID
  
  ← READY OK
