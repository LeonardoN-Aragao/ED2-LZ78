#include <iostream>
#include <fstream>
#include <vector>
#include <string>

/*
    cadeia := '' # inicializa com a cadeia de tamanho 0
    D.insere(cadeia)
    enquanto c := leia_novo_caractere()
    se D contém cadeia concatenada com c
        cadeia := cadeia concatenada com c
    senão
        imprime_na_saida([D.código(cadeia), c])
        D.insere(cadeia concatenada com c)
        cadeia = ''
    fim se
    fim enquanto
    imprime_na_saida([D.código(cadeia), ''])
*/

bool hasSequence(std::vector<std::string> vet, std::string value)
{
    for (int i = 0; i < vet.size();i++)
        if (vet[i] == value)
        return true;
    return false;
}

int sequencePosition(std::vector<std::string> vet, std::string value)
{
    for (int i = 0; i < vet.size();i++)
        if (vet[i] == value)
            return i+1;
    return 0;
}

std::string LZ78(std::string file_name){

    std::string saida = "";
    std::fstream file;
    file.open(file_name,std::fstream::in);

    if(file.is_open()) {
        std::vector<std::string> dicionario;
        std::string sequencia = "";

        while(!file.eof()) {
            char c;
            c = file.get();
            
            if (hasSequence(dicionario,sequencia + c)) {
                sequencia = sequencia + c;
            }
            else {
                if(c != EOF){
                    saida = saida + "[" + std::to_string(sequencePosition(dicionario,sequencia))+","+ c + "] ";
                    dicionario.push_back(sequencia + c);
                    sequencia = "";
                }
                else{
                    saida = saida + "[" + std::to_string(sequencePosition(dicionario,sequencia)) + ",Null] ";
                }
            }                 
        }
        std::cout<<"saida = "<<saida<<"\n";
        std::cout<<"\nImprimindo dicionario\n\n";
        for (int i = 0; i < dicionario.size();i++){
            std::cout<<i+1<<" \""<<dicionario[i]<<"\"\n";
        }
    }
    else {
        std::cout<<"erro ao abrir o arquivo "<<file_name<<".\n";
    }   

    return saida;
}

void decodificador(std::string saida){
    
    std::vector<std::string> dicionario;
    std::string sequencia;

    for(int i = 0; i < saida.size(); i++){
        //Pula simbolos
        while(saida[i] == '[' || saida[i] == ']' || saida[i] == ' ')
            i++;
        char aux = saida[i];
        int pos = atoi(&aux);
        
        //Pula virgula
        i = i + 2;
        char letra = saida[i];
        sequencia = "";
        
        //Verifica se não chegou no "Null"
        if(saida[i+1] == ']'){
            //std::cout<<pos<<"\n";
            if(pos == 0){
                dicionario.push_back(sequencia+letra);
                std::cout<<letra;
            }
            else{
                sequencia = dicionario[pos-1] + letra;
                dicionario.push_back(sequencia);
                std::cout<<sequencia;
            }
        }
        else{
            if(pos != 0)
                std::cout<<dicionario[pos-1];
            /*
            std::cout<<"\n\nImprimindo dicionario\n\n";
            for (int i = 0; i < dicionario.size();i++){
                std::cout<<i<<" "<<dicionario[i]<<"\n";
            }
            */
            break;
        }
    }
    std::cout<<"\n";
}

int main(int tam_arg,char ** arg){

    std::string saida;
    if(tam_arg == 2){
        saida = LZ78(arg[1]);
    }

    std::cout<<"\nDECODIFICANDO\n\n";
    decodificador(saida);

    return 0;
}