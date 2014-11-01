#include <stdio.h>
#include <stdlib.h>

class Matriz
{
	
	private:
		int n_linhas,n_colunas;	
		int **dados;
		
	public:
		Matriz(int l, int c)
		{
			if(l>0 && c>0)
			{
				dados = new int*[l];
				for(int i=0; i<l; i++)
					dados[i] = new int[c];
					
				this->n_linhas = l;
				this->n_colunas = c;
			}
			else
			{
				printf("Erro ao criar Matriz de ordem %ix%i\n",l,c);
			}
		}
		
		~Matriz()
		{
			for(int i=0; i < this->n_linhas; i++)
				delete [] dados[i];
			delete [] dados;
		}
		
		int get_linhas() const{ return this->n_linhas; }
		int get_colunas() const{ return this->n_colunas;}
		
		void set_valor(int l, int c, int val)
		{
			if(l <= this->n_linhas && c <= this->n_colunas)
				this->dados[l][c] = val;
			else
				printf("Posicao informada nao existe!\n");
		}
		
		void mostra() const
		{
			for(int i=0; i<this->n_linhas; i++){
				for(int j=0; j<this->n_colunas; j++){
					printf("%i ",this->dados[i][j]);
				}
				printf("\n");
			}
		}
		
		void preenche(){
			
			for(int i=0; i<this->n_linhas; i++){
				for(int j=0; j < this->n_colunas; j++){
					scanf("%i", &this->dados[i][j]);
				}
			}
			
		}
		
		bool e_igual(const Matriz &B) const
		{
			if(this->n_linhas != B.get_linhas() && this->n_colunas != B.get_colunas())
				return false;
			
			for(int i=0; i<this->n_linhas; i++)
				for(int j=0; j<this->n_colunas; j++)
					if(this->dados[i][j] != B.get(i,j))
						return false;
			return true;
		}
		
		bool e_diferente(const Matriz &B) const
		{
			if(!this->e_igual(B))
				return true;
			return false;
		}
		
		int get(int l, int c) const
		{
			if(l<this->n_linhas && c<this->n_colunas)
				return this->dados[l][c];
			return 0;
		}
		
		Matriz adiciona(const Matriz &B) const
		{
			Matriz C(this->n_linhas,this->n_colunas);
			for(int i=0; i<this->n_linhas; i++){
				for(int j=0; j<this->n_colunas; j++){
					C.set_valor(i,j, this->dados[i][j] + B.get(i,j));
				}
			}
			return C;
		}
		
		Matriz subtrae(const Matriz &B) const
		{
			Matriz C(this->n_linhas,this->n_colunas);
			for(int i=0; i<this->n_linhas; i++){
				for(int j=0; j<this->n_colunas; j++){
					C.set_valor(i,j, this->dados[i][j] - B.get(i,j));
				}
			}
			return C;
		}
		
		Matriz multiplica(const Matriz &B) const
		{
			Matriz C(this->n_linhas,B.get_colunas());
			int val=0;
			for(int i=0; i<this->n_linhas;i++)
			{
				for(int j=0; j<B.get_colunas(); j++)
				{
					val = 0;
					for(int k=0; k<this->n_colunas; k++)
					{
						val += this->dados[i][k] * B.get(k,j);
					}
					C.set_valor(i,j,val);
				}
			}
			return C;
		}
		
		Matriz multiplica_constante(int K) const
		{
			Matriz C(this->n_linhas,this->n_colunas);
			
			for(int i=0; i<this->n_linhas;i++)
			{
				for(int j=0; j<this->n_colunas; j++)
				{
					C.set_valor(i,j,this->dados[i][j] * K);
				}
			}
			return C;
		}
		Matriz operator*(int K)
		{
			return this->multiplica_constante(K);
		}
		
		Matriz operator*(const Matriz &B)
		{
			
			if(this->n_colunas != B.get_linhas()){
				printf("Nao pode ser efetuado a multiplicacao das matrizes\n");
				exit(1);
			}
			
			return this->multiplica(B);
		}
		
		Matriz operator-(const Matriz &B)
		{
			if(this->n_linhas != B.get_linhas() || this->n_colunas != B.get_colunas())
			{
				printf("Matrizes de ordem diferentes\n");
				exit(1);
			}
			return this->subtrae(B);
			
		}
		
		Matriz operator+(const Matriz &B)
		{
			if(this->n_linhas != B.get_linhas() || this->n_colunas != B.get_colunas())
			{
				printf("Matrizes de ordem diferentes\n");
				exit(1);
			}
			return this->adiciona(B);
			
		}
	
		
		void operator=(const Matriz &B)
		{
			if(this->n_linhas != B.get_linhas() || this->n_colunas != B.get_colunas())
			{
				printf("Matrizes de ordem diferentes\n");
				exit(1);
			}
			
			Matriz C(this->n_linhas,this->n_colunas);
			for(int i=0; i<this->n_linhas; i++){
				for(int j=0; j<this->n_colunas; j++){
					this->set_valor(i,j,B.get(i,j));
				}
			}
			
		}
		
		
		Matriz transposta() const
		{
			Matriz C(this->n_colunas, this->n_linhas);
			
			for(int i=0; i<this->n_colunas; i++){
				for(int j=0; j<this->n_linhas; j++){
					C.set_valor(i,j, this->dados[j][i]);
				}
			}
			return C;
		}
		
		
		Matriz potencia(int pot) const
		{
			Matriz C(this->n_linhas,this->n_colunas);
			C = (*this);
			for(int i=1; i<pot; i++){
				C = C.multiplica((*this));
			}
			return C;
		}
		
		bool e_triang_sup() const
		{
			if(this->n_linhas != this->n_colunas)
				return false;
				
			for(int i=1; i<this->n_linhas; i++){
				for(int j=0; j<i; j++){
					if(this->dados[i][j]!=0)
						return false;
				}
			}
			return true;
		}
		
		bool e_triang_inf() const
		{
			if(this->n_linhas != this->n_colunas)
				return false;
				
			for(int i=0; i<this->n_linhas-1; i++){
				for(int j=1+i; j<this->n_colunas; j++){
					if(this->dados[i][j]!=0)
						return false;
				}
			}
			return true;
		}
		
		bool e_simetrica() const
		{
			
			if(this->n_linhas != this->n_colunas)
				return false;
				
			if(this->e_igual(this->transposta()))
				return true;
			
			return false;
			
		}
		
		bool e_anti_simetrica() const
		{
			
			if(this->n_linhas != this->n_colunas)
				return false;
			
			for(int i=0; i<this->n_linhas; i++)
			{
				for(int j=i; j<this->n_colunas; j++)
				{
					if(this->dados[i][j] != (this->dados[j][i] * (0-1))){
						return false;
					}
				}
			}
			return true;
		}
		
		
		
	
};