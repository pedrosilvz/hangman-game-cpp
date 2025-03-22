#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <vector>
#include <locale.h>
#include <fstream>
#include <ctime>
using namespace std;

string palavra_secreta;          // string serve para substiuir o uso de char[] 
map <char, bool> chutou;         // map � uma estrutura de dados que armazena pares de chave e valor, nesse caso a chave � do tipo char e o valor � do tipo bool, ele come�a vazio, nesse caso vai verificar qual letra foi chutada pelo usu�rio e quais n�o foram
vector <char> chutes_errados;    // vector n�o tem um tamanho fixo, ele pode ser aumentado ou diminuido, ele � uma estrutura de dados que armazena um conjunto de elementos do mesmo tipo



bool letra_existe(char chute){                    
    for (char letra : palavra_secreta) {          // substitui o uso de for(int i = 0; i < palavra_secreta.size(); i++)
        if (chute == letra) {   
            return true;       // essa fun��o serve para verificar se a letra chutada pelo usu�rio corresponde � alguam letra da palavra secreta, ela � interada por um loop que percorre a palavra secreta
        }
    }
    return false;
}


bool nao_acertou() {
    for (char letra : palavra_secreta) {
        if (!chutou[letra]) {
            return true;
        }
    } 
    return false;
}


bool nao_enforcou() {
   return chutes_errados.size() < 5;
}


void inicio () {
    cout << "***************************" << endl;
    cout << "*                         *" << endl;
    cout << "*      JOGO DA FORCA      *" << endl;
    cout << "*                         *" << endl;
    cout << "***************************" << endl;

}


void imprime_palavra() {
    for (char letra : palavra_secreta){     // vai percorrer a palavra secreta e verificar se a letra chutada pelo usu�rio corresponde a alguma letra da palavra secreta
        if (chutou[letra]) {      
            cout << letra << " ";
        } else {
            cout << "_ ";
        }
    }
}


void imprime_erros() {
    cout << "Chutes errados: ";
    for (char letra : chutes_errados) {
        cout << letra << " ";
 }
    cout << endl;
}


void chuta (){
    cout << "Qual � seu chute? ";
    char chute;
    cin >> chute;
    chutou[chute] = true;                        //  essa linha serve para armazenar o chute do usu�rio no map
    cout << "Seu chute foi: " << chute << endl;

    cout << endl;

    if (letra_existe(chute)) {  
        cout << "------------------------------------------------------" << endl;
        cout << "    Voc� Acertou! Seu chute est� na palavra secreta!  " << endl;
        cout << "------------------------------------------------------" << endl;
    } else {
        cout << "------------------------------------------------------" << endl;
        cout << "  Voc� errou! Seu chute n�o est� na palavra secreta!  " << endl;
        cout << "------------------------------------------------------" << endl;
        chutes_errados.push_back(chute);                                                    // essa linha serve para armazenar o chute errado do usu�rio no vector
    }
}


vector<string> ler_arquivo(){
    ifstream arquivo;               // ifstream � uma classe que serve para abrir arquivos
    arquivo.open("words.txt");

    if (arquivo.is_open() == false) {       // essa linha serve para verificar se o arquivo foi aberto corretamente
        cout << "Erro ao abrir o arquivo. O programa foi encerrado!" << endl << endl;
        exit(0);
    }

    int quantidade_palavras;            
    arquivo >> quantidade_palavras;         // lemos a quantidade de palavras que tem no arquivo


    vector<string> palavras_do_arquivo; 

    for (int i = 0; i < quantidade_palavras; i++) {
        string palavra_lida;
        arquivo >> palavra_lida;                        // essa linha serve para ler a palavra do arquivo
        palavras_do_arquivo.push_back(palavra_lida);    // essa linha serve para armazenar a palavra lida no vector palavras_do_arquivo
    }
    arquivo.close();
    return palavras_do_arquivo; 
}


void sorteia_palavra() {
    vector <string> palavras_recebidas = ler_arquivo();    // essa linha serve para armazenar as palavras lidas no vector palavras_recebidas
    srand (time(NULL));                                     // essa linha serve para gerar um n�mero aleat�rio
    int indice_sorteado = rand() % palavras_recebidas.size();
    palavra_secreta = palavras_recebidas[indice_sorteado];
}


void salva_arquivo(vector<string> nova_lista) {
    ofstream arquivo;                               // a diferen�a entre ofstream e ifstream � que ofstream serve para escrever no arquivo
    arquivo.open("words.txt");

    if (arquivo.is_open() == false) {
        cout << "Erro ao abrir o arquivo. O programa foi encerrado!" << endl << endl;
        exit(0);
   }

    arquivo << nova_lista.size() << endl;       // vai escrever a quantidade de palavras que tem na nova lista
    for (string palavra : nova_lista) {         // vai passar por todas as palavras dessa lista (os valores da lista s�o strings ent�o a vari�vel palavra � do tipo string)
        arquivo << palavra << endl;             // imprime essa palavra no arquivo
    }

    arquivo.close();
}

void adciona_palavra() {
        cout << "Digite a nova palavra (utilize letras mai�sculas): ";
        string nova_palavra;
        cin >> nova_palavra;

        vector<string> lista_palavras = ler_arquivo();      // ler_arquivo() serve para ler as palavras do arquivo e armazenar no vector lista_palavras
        lista_palavras.push_back(nova_palavra);

        salva_arquivo(lista_palavras);                      // salva_arquivo() serve para salvar a nova palavra no arquivo
}


int main () {
    setlocale(LC_ALL, "Portuguese");    

    inicio();
    ler_arquivo();
    sorteia_palavra();

    while (nao_acertou() && nao_enforcou()) { 

        imprime_erros();
        imprime_palavra();
        cout << endl << endl; 
        chuta ();
        cout << endl << endl;
    }

    cout << "   - Fim de Jogo! A palavra secreta era: " << palavra_secreta << endl;

    if(nao_acertou()) {
        cout << "======================================================" << endl;
        cout << "               Voc� perdeu! Tente novamente!          " << endl;
        cout << "======================================================" << endl;
    } else {
        cout << "======================================================" << endl;
        cout << "               Parab�ns! Voc� ganhou!                 " << endl;
        cout << "======================================================" << endl;

        cout << "Voc� deseja adcionar uma nova palavra no jogo? (S/N) ";
        char resposta;
        cin >> resposta;

        if (resposta == 'S') {
            adciona_palavra();
        }
    }

}