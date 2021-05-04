#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<time.h>
#include<sys/resource.h>
double memoria() {
	struct rusage r ;
	getrusage(RUSAGE_SELF, &r) ;
	return (double) r.ru_maxrss ;
}

int main(int argc, char ** argv) {
	double t = clock() ;
	if (strcmp(argv[1], "-g")==0){
		if (atoi(argv[3])<0 || atoi(argv[3]) >100){
			t = (clock()-t)/CLOCKS_PER_SEC ; printf("tiempo : %lf\n",t) ;
	    	printf("memoria : %lf KB\n", memoria()) ;
	    	perror("La popularidad que buscas no es válida.\n");
	    	exit(EXIT_FAILURE);
		}
	    FILE *genres = fopen("genres.txt", "r");
		int n = 13000000 ; 
	    
		//Esto no debería pasar nunca, pero aún así supongo que es buena práctica :)
	    if (genres == 0){
	        fprintf(stderr, "Failed to open file 'genres.txt' for reading\n");
	        return 1;
	    }
	    char **names; names=  malloc(n*sizeof(char*)) ;
	    char **id; id = malloc(n*sizeof(char*)) ;
	    char *buffer1 ; buffer1 = malloc(4000*sizeof(char)) ;
	    char *line ; int counter = 0 ;

	    for (int i = 0; i < n && fgets(buffer1, 4000, genres) != 0; i++){

	        buffer1[strcspn(buffer1, "\n")] = '\0';
	        line = strtok(strdup(buffer1), ";") ;
	        if (strcmp(line, argv[2]) == 0){
	        	line = strtok(NULL, ";") ;
	        	id[counter] = line;
	        	line = strtok(NULL, "\n") ;
	        	names[counter] = line ;
	        	counter += 1 ;

	        }
	    }
	    //Si no agregue nada en la primera posición, es porque el archivo de texto no conoce el género escrito
	    if (names[0] == NULL){
	    	t = (clock()-t)/CLOCKS_PER_SEC ; printf("tiempo : %lf\n",t) ;
	    	printf("memoria : %lf KB\n", memoria()) ;
	    	perror("El género que ingresaste no existe en genres.txt.\n");
	    	exit(EXIT_FAILURE); 	
	    }
	    names = realloc(names, counter*sizeof(char*)) ; id = realloc(id, counter*sizeof(char*)) ;

	    FILE *songs = fopen("songs.txt", "r") ;
	    if (songs == 0){
	        fprintf(stderr, "Failed to open file 'songs.txt' for reading\n");
	        return 1;
	    }
	    char *buffer ; buffer = malloc(4000*sizeof(char)) ;
	    int p ;
	    char **popularity ; popularity = malloc(counter*sizeof(char*)) ;
	    for (int i =0 ; i<counter; i++){
		    for (int j = 0; j < n && fgets(buffer, 4000, songs) != 0; j++){
		        buffer[strcspn(buffer, "\n")] = '\0';
		        line = strtok(strdup(buffer), ";") ;
		        if (strcmp(line, id[i]) == 0){
		        	line = strtok(NULL, ";") ;
		        	popularity[i] = line ;
		        	p = atoi(line) ;
		        	id[i] = NULL ;
		        	break ; 	
		        }
		    }
	    }
	    printf("%s\n",argv[2]) ;
	    int average = 0 ; int number ; //Estamos usando int para que se parezca más al enunciado, podría cambiar esto por double
	    //y usar strtod en vez de atoi, pero los  números son un poco más feos (y el resultado final es lo mismo en términos prácticos).
	    for (int i = 0; i < counter; i++){
	        if(names[i] != NULL) {
	        	number = 1 ;
	        	average = atoi(popularity[i]) ; 
		        for (int q = i + 1 ; q < counter ; q++){
		        	if (names[q] != NULL){
			        	if (strcmp(names[i],names[q]) == 0) {
			        		names[q] = NULL ;
			        		average += atoi(popularity[q]) ; popularity[q] = NULL ;
			        		number += 1 ;	
		        		}
		        	}
	    		}
	    		if (average/number >= atoi(argv[3])) {
	    			printf("\t%-s : %d\n", names[i], average/number) ;
	    		}
		    	number = 0 ;
	    	}
	    	names[i] = NULL ;
	    }
	 	
 		free(popularity) ;
 		free(names); free(id) ;
	 	free(buffer1) ; free(buffer) ;
	    fclose(genres); fclose(songs); //fclose(genres1);
	    t = (clock()-t)/CLOCKS_PER_SEC ; printf("tiempo : %lf\n",t) ;
	    printf("memoria : %lf KB\n", memoria()) ;
	    return 0;
	}

	if (strcmp(argv[1],"-p")==0){
		if (strcmp(argv[2], "Major") != 0 && strcmp(argv[2], "Minor")){
			t = (clock()-t)/CLOCKS_PER_SEC ; printf("tiempo : %lf\n",t) ;
	    	printf("memoria : %lf KB\n", memoria()) ;
	    	perror("Las canciones sólo son de modo 'Major' o 'Minor'.\n");
	    	exit(EXIT_FAILURE); 
		}

	    FILE *songs = fopen("songs.txt", "r") ;
		int n = 13000000 ; // number_lines(genres1);
	    if (songs == 0){
	        fprintf(stderr, "Failed to open file 'songs.txt' for reading\n");
	        return 1;
	    }
	    char **id; id = malloc(n*sizeof(char*)) ;
	    char *buffer1 ; buffer1 = malloc(4000*sizeof(char)) ;
	    char *line ; int counter = 0 ; char *possible_id ;

	    for (int i = 0; i < n && fgets(buffer1, 4000, songs) != 0; i++){

	        buffer1[strcspn(buffer1, "\n")] = '\0';
	        line = strtok(strdup(buffer1), ";") ;
	        possible_id = line ;
	        line = strtok(NULL, ";") ;
	        line = strtok(NULL, "\n") ;
	        if (strcmp(line, argv[2]) == 0){
	        	id[counter] = possible_id ;
	        	counter += 1 ;
	        }
        }
        id = realloc(id, counter*sizeof(char*)) ;

        FILE *genres = fopen("genres.txt", "r");
        if (genres == 0){
	        fprintf(stderr, "Failed to open file 'genres.txt' for reading\n");
	        return 1;
	    }

        char **g ; g = malloc(n*sizeof(char*)) ; 
        int *gen ; gen = malloc(n*sizeof(int)) ; char *one_genre ; int amount_genres;
        char *buffer ; buffer = malloc(4000*sizeof(char)) ;
	    char *l ; int c = 0 ;
	    
	    for (int i = 0 ; i<n && fgets(buffer, 4000, genres); i++){
        	buffer[strcspn(buffer, "\n")] = '\0';
	        l = strtok(strdup(buffer), ";") ;
        	if (i == 0){
        		one_genre = l ; amount_genres = 1; g[amount_genres-1] = one_genre ; gen[amount_genres-1] = 0 ;
        		l = strtok(NULL, ";") ; l = strtok(NULL, "\n") ;
        	}
        	else{
 				int flag = 0 ;
	        	for (int j = 0; j<amount_genres; j++){
	        		if (strcmp(g[j], l) == 0){
	        			flag = 1 ;
	        			break ;
	        		}
	        	}
	        	if (flag == 0){
	        		one_genre = l ; amount_genres += 1; 
	        		g = realloc(g, amount_genres*sizeof(char*)); g[amount_genres-1] = one_genre ;
	        		gen = realloc(gen, amount_genres*sizeof(int)) ; gen[amount_genres-1] = 0 ;
	        	}
	        	l = strtok(NULL, ";") ;
	        	l = strtok(NULL, "\n") ;
	        }
        }

        FILE *genres1 = fopen("genres.txt", "r") ;
        if (genres1 == 0){
	        fprintf(stderr, "Failed to open file 'genres.txt' for reading\n");
	        return 1;
	    }
        char *buffer2 ; buffer2 = malloc(4000*sizeof(char)) ;
        
		for(int z=0; z<counter; z++){
			if(id[z] != NULL){
				for (int i = 0 ; i<n && fgets(buffer2, 4000, genres1); i++){
		        	buffer2[strcspn(buffer2, "\n")] = '\0';
			        l = strtok(strdup(buffer2), ";") ; char* genre = l ; 
	   				l = strtok(NULL, ";") ;
	   				if (strcmp(l, id[z]) == 0){
	   					for(int j = 0; j<amount_genres; j++){
							if (strcmp(genre, g[j]) == 0){
								gen[j] += 1 ; id[z] = NULL ;
								break ;
							}
						}
						break;
	   				}
	   				l = strtok(NULL, "\n") ;
   				}
			}
		}
	   		   
        for (int i = 0; i<amount_genres; i++){
        	printf("%s: %d\n", g[i], gen[i]) ;
        }

        free(id) ;
        free(g) ; free(gen) ;  
        free(buffer) ; free(buffer1) ; free(buffer2) ;
        fclose(songs) ; fclose(genres) ; fclose(genres1) ;

	    t = (clock()-t)/CLOCKS_PER_SEC ; printf("tiempo : %lf\n",t) ;
	    printf("memoria : %lf KB\n", memoria()) ;
		return 0 ;
	}
	else {
		perror("El input ingresado en la terminal es incorrecto.\n");
	    exit(EXIT_FAILURE);
	}
	return 0 ;
}