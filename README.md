# Remote Backup

## Functional requirements

1. Identificazione dell'utente (client -> server)
2. Creazione dell'utente (lato server)
3. Accesso allo spazio (TCP)
    1. Identificazione del client e delle cartelle sul client (lato server)
        (codice identificativo per la singola macchina fisica da comunicare al server
        che lo utilizza per riconoscere il client durante l'accesso alle cartelle)
    2. Inizializzazione della cartella attiva (creazione se non esiste)
 4. Scansione periodica della cartella per eventuali modifiche tramite metadati del server [eventualmente cachato su file su client] (lato client) 
    1. Aggiornamento file sul server (aggiunta, cancellazione, modifica)

## Protocollo

```plantuml
Client -> Server : connect()

Client -> Server : Login Request
Client <- Server : Login Response

Client -> Server : Workspace choice
Client <- Server : Workspace status

Client -> Server : Server Metadata Request
Client <- Server : Server Metadata Response

Client -> Server : Add/Delete/Modify message
Client <- Server : Add/Delete/Modify response
```

### Formato dei messaggi

- Login request:  
  - Code
  - Username
  - Password
- Login response:
  - Code 
  - Status
- Workspace choice: 
  - Code
  - Path
  - Machine ID
- Workspace status
  - Code
  - New/Already exists
- Server Metadata request
  - Code
- Server Metadata Response
  - Code
  - [ Metadata information (<filename, checksum> or simply <directory, >) ]
- Add/Delete/Modify message
  - Code
  - Action (ADD_FILE, ADD_DIRECTORY, UPDATE, DELETE)
  - Path
  - Size*
  - Payload file*
- Add/Delete/Modify response
  - Code
  - Path
  - Status
  - Checksum*
- Bad Request:
  - Code
  - Message

## Design

### Client

```plantuml

class Configuration{
    path : std::string
    machineID : std::string
    username : std::string
    password : std::string
    ipAddress : std::string
    port : long

    Constructor(configFile)
}

class PBAuthentication{
    username : std::string
    password : std::string
}

class PBWorkSpaceChoice{
    path : std::string
    machineID : std::string
}

class Main{

}

class sendToServer{}
class receiveFromServer{}

class Socket{
    fd : int
}

Main - Configuration
Main -- PBAuthentication
Main -- PBWorkSpaceChoice
Main -- Socket
receiveFromServer -- FileWatcher
sendToServer -- FileWatcher
FileWatcher -- JobQueue

class DirectoryEntry{
    name : std::string
    visited : bool
    delete()
    setVisited()
    getNotVisited()
}

class JobQueue{
  add(path, action)
  getLastAndSetSent()
  remove()
}

JobQueue --"*" Job

class Job{
    action : enum
    sent : bool
}

Job "0..2" -- DirectoryEntry

class File{
    checksum : std::string
    lastEditDateTime : time
    std::string computeChecksum()
    setChecksum()
    setLastEditDateTime()
}

class Directory{
    addFile(...) 
    addDirectory(relativePath)
    getFile(path)
    getDirectory(path)
}

class FileWatcher{}

Directory --|> DirectoryEntry
File --|> DirectoryEntry

Directory -- "*" DirectoryEntry : contains

Main -- FileWatcher
FileWatcher - Directory : root

class PBDirectoryEntry{
    required name
    required type
    optional checksum
    optional date  
}

DirectoryEntry --"0..1" PBDirectoryEntry 

class Checksum{
  std::string computeChecksum()
}

File--> Checksum 
```

Thread : 
- scansione del file system periodica [dopo quella iniziale], aggiornamento data di modifica e inserimento in coda e inserimento/rimozione/modifica della directoryEntry
- invio dati al server dalla coda
- ricezione dati dal server, rimozione della coda e controllo checksum


### Server
```plantuml
class Main{}

Main -- ServerSocket


class Workspace{
    localFolder : std::string 
    lastActivity? : time
    std::string computeServerPath(user, machine, directory)
}

note top of Workspace
localFolder è il path del server
della cartella di cui eseguire il backup
(es /user/Machine/folderID)
ottenuto da computeServerPath().

Per ogni cartella /user/Machine vi sarà un file
mapping.csv che traduce absolute path client in 
cartella relativa sul server
end note

Workspace -- Socket

class Socket{
    fd : int
}

class Authentication {
    bool authenticate(user, pw)
}

class PBAuthentication{
    username : std::string
    password : std::string
}

class PBWorkSpaceChoice{
    path : std::string
    machineID : std::string
}

Main -- "*" Workspace
Workspace -- PBAuthentication
Workspace -- PBWorkSpaceChoice

Workspace "*" -- Authentication

class Checksum{
    std::string computeChecksum()
}

class PBDirectoryEntry{
    required name
    required type
    optional checksum
    optional date  
}

Workspace "*" --> Checksum
Workspace --"*" PBDirectoryEntry : contains >

class PBMetaInfoReq {
    required Action
    required path
    optional size
}

class PBMetaInfoRes {
    required Status
    optional checksum
}

```

## Iteration 1
Chi testa chi
```plantuml
:Angelica: --> :Roberto:
:Roberto: -right-> :Matteo:
:Matteo: --> :Angelica:
```