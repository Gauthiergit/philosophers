#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Structure pour stocker des informations sur le thread et les ressources partagées
typedef struct {
    pthread_mutex_t* forks; // Tableau de mutex pour les fourchettes
    pthread_mutex_t print_mutex; // Mutex pour l'affichage
    int num_forks; // Nombre de fourchettes
} ThreadData;

// Structure pour stocker des informations sur le thread
typedef struct {
    int thread_id; // Identifiant du thread
    ThreadData* data; // Pointeur vers les données partagées
} ThreadInfo;

// Fonction pour simuler manger
void manger(ThreadInfo* info) {
    printf("Thread %d prend la fourchette %d\n", info->thread_id, info->thread_id);
    sleep(3); // Simuler le temps de manger
    printf("Thread %d libère la fourchette %d\n", info->thread_id, info->thread_id);
}

// Fonction exécutée par chaque thread
void* thread_fonction(void* arg) {
    ThreadInfo* info = (ThreadInfo*)arg;
    int left_fork = info->thread_id;
    int right_fork = (info->thread_id + 1) % info->data->num_forks;

    pthread_mutex_lock(&info->data->forks[left_fork]); // Prendre la fourchette gauche
    pthread_mutex_lock(&info->data->forks[right_fork]); // Prendre la fourchette droite

    pthread_mutex_lock(&info->data->print_mutex);
    manger(info); // Manger
    pthread_mutex_unlock(&info->data->print_mutex);

    pthread_mutex_unlock(&info->data->forks[right_fork]); // Libérer la fourchette droite
    pthread_mutex_unlock(&info->data->forks[left_fork]); // Libérer la fourchette gauche

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number of threads>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    if (num_threads <= 0) {
        printf("Invalid number of threads\n");
        return 1;
    }

    pthread_t threads[num_threads];
    ThreadInfo info[num_threads];
    ThreadData data;

    // Initialisation du nombre de fourchettes
    data.num_forks = num_threads;

    // Allocation dynamique du tableau de mutex pour les fourchettes
    data.forks = (pthread_mutex_t*)malloc(num_threads * sizeof(pthread_mutex_t));
    if (data.forks == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        return 1;
    }

    // Initialisation des mutex pour chaque fourchette
    for (int i = 0; i < num_threads; i++) {
        pthread_mutex_init(&data.forks[i], NULL);
    }

    // Initialisation du mutex pour l'affichage
    pthread_mutex_init(&data.print_mutex, NULL);

    // Créer les threads
    for (int i = 0; i < num_threads; i++) {
        info[i].thread_id = i;
        info[i].data = &data;
        pthread_create(&threads[i], NULL, thread_fonction, (void*)&info[i]);
    }

    // Attendre la fin des threads
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destruction des mutex pour chaque fourchette
    for (int i = 0; i < num_threads; i++) {
        pthread_mutex_destroy(&data.forks[i]);
    }

    // Destruction du mutex pour l'affichage
    pthread_mutex_destroy(&data.print_mutex);

    // Libération de la mémoire allouée pour le tableau de mutex
    free(data.forks);

    return 0;
}
