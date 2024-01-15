#include <stdio.h>
#include <stdlib.h>
//εισάγουμε τις απαραίτητες βιβλιοθήκες

#define SIZE 2
#define STARTPIXELS 10 
#define WIDTH (18 - 14)
#define HEIGHT (22 - 14)
#define IMAGESIZE (34 - 14)
#define twentyfourBYTE (28-14)
//ορίζω τις θέσεις των πληροφοριών που θα χρησιμοποιήσω από τον πίνακα ως σταθερές 
//επειδή παρακάτω έχω σπάσει τα headers σε δύο πίνακες για να μην υπάρξει κάποιο σφάλμα
//για τις θέσεις των πληροφοριών που βρίσκονται στον δεύτερο πίνακα αφαιρώ το σύνολο των στοιχείων του 
//πρώτου πίνακα

int main() {
    char headers[14];//ορίζω τον πρώτο πίνακα με τις 14 πρώτες πληροφορίες
    char *otherdata;//ορίζω τους δείκτες που θα με βοηθήσουν στην δέσμευση μνήμης για τους άλλους μου δύο πίνακες
    char *pixels;
    int read = fread(headers, sizeof(char), 14, stdin);// με την χρήση της fread διαβάζω τα 14 πρώτα στοιχεία
    if (read < 14) {//ορίζοντας πρώτα που θα τοποθετηθούν, το μέγεθος,το πλήθος , απο πού
        exit(1);//αν αποτύχει η ανάγνωση και των 14 (αφού επιστρέφει 1 για κάθε ανάγνωση)
    }// το πρόγραμμα τερματίζει με έξοδο 1
    if (headers[0] != 'B' || headers[1] != 'M') {//εδώ επιβεβαίωνω ότι το αρχείο έχει την μορφή bmp 
        fprintf(stderr, "Error: not a BMP file\n");// που επιθυμούμε
        exit(1);
    }
    int pixel_offset;
    pixel_offset = *(unsigned int *)(headers + STARTPIXELS);//βρίσκουμε που ξεκινάνε τα πίξελ δηλαδή τον αριθμο των headers
    if(pixel_offset<54){//ελέγχουμε ότι τα αρχεία έχουν το κατάλληλο αριθμό headers
        exit(1);
    }
    int diafora = pixel_offset - 14;
    otherdata = malloc(diafora * sizeof(char));//δημιουργώ τον πίνακα που θα αποθηκεύσει τα υπόλοιπα headers
    //από εδώ και κάτω προτιμώ την malloc επειδή δεν έχουμε συγκεκρίμενα νούμερα και επιθυμούμε να δεσμεύσουμε μόνο όσα χρειαζόμαστε 
    int readata = fread(otherdata, sizeof(char), diafora, stdin);
    if (readata != diafora) {//ελέγχουμε ότι η ανάγνωση πέτυχε
        exit(1);
    }
    int byte24=*(unsigned int*)(otherdata+twentyfourBYTE);
    if(byte24!=24){
      exit(1);//αφού πρέπει να χρησιμοποιεί 24-bit για αναπαράσταση χρώματος
    }
    int width, height, imagesize;//εδώ υπολογίζουμε το πλάτος ,ύψος και το μέγεθος της εικόνας σύμφωνα με την τακτική που ανέφερα
    width = *(unsigned int *)(otherdata + WIDTH);
    height = *(unsigned int *)(otherdata + HEIGHT);
    imagesize = *(unsigned int *)(otherdata + IMAGESIZE);
    pixels = malloc(imagesize * sizeof(char));//δημιουργλω έναν μονοδίαστατο με τα πίξελ και το πάντινγκ
    int readpixel = fread(pixels, sizeof(char), imagesize, stdin);
    if (readpixel != imagesize) {
        exit(1);//ελέγχουμε ότι η ανάγνωση πέτυχε
    }
    char ***image = malloc(height * sizeof(char **));
    for (int i = 0; i < height; i++) {
        image[i] = malloc(width * sizeof(char *));
        for (int j = 0; j < width; j++) {
            image[i][j] = malloc(3 * sizeof(char));
        }// έπειτα δημιουργώ έναν τρισδιάστατο για να περάσουμε τα πίξελ το προτιμάμαι επειδή είναι 3byte κάθε πίξελ
    }
    int c = 0; // counter
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                if (pixels[c] == '\0') {
                    c++;
                    continue;
                }
                image[i][j][k] = pixels[c];
                c++;
            }//εδώ περνάμε τα πίξελ βγάζοντας το πάντινγκ
        }
    }
    int new_height = width;
    int new_width = height;//αλλάζω τις διαστάσεις
    char ***rotated = malloc(new_height * sizeof(char **));
    for (int i = 0; i < new_height; i++) {
        rotated[i] = malloc(new_width * sizeof(char *));
        for (int j = 0; j < new_width; j++) {
            rotated[i][j] = malloc(3 * sizeof(char));
        }// και δημιουργώ τον πίνακα που θα μπουν τα γυρισμένα πίξελ
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                rotated[width - 1 - j][i][k] = image[i][j][k];
            }//αναπαράστισα τους πίνακες στο χαρτί και έπειτα από μελέτη παρατήρησα οτι ισχύει η παραπάνω συνθηκη
        }//ενώ θέλουμε να την γυρίσουμε δεξιόστροφα πρέπει να την γυρίσουμε αριστερά λόγω της διαφορας χρωμάτων που βλέπει ο υπολογιστής και εμείς
    }
    int padding = (new_width * 3) % 4;// εδώ υπολογίζουμε το καινούργιο πάντιγκ αφού θέλουμε οι γραμμές να έχουν μήκος πολ/σο του 4 
    //προκύπτει το %4 και λόγω των 3 byte το *3
    *(unsigned int *)(otherdata + WIDTH) = new_width;
    *(unsigned int *)(otherdata + HEIGHT) = new_height;// εδώ αλλάζουμε τις διαστάσεις στα headers της καινούριας εικόνας 
    *(unsigned int *)(headers + SIZE) = 14 + diafora + (new_width * 3 * new_height) + (padding * new_height);
    // εδώ υπολογίζουμε το μέγεθος του αρχείου καθώς περιέχονται τα χέντερς το συνολικό πάντινγκ και όλα τα πίξελ
    *(unsigned int *)(otherdata + IMAGESIZE) = (new_width * 3 * new_height) + (padding * new_height);
    // ενώ το μέγεθος της εικόνας μόνο από το το συνολικό πάντινγκ και όλα τα πίξελ
    fwrite(headers, sizeof(char), 14, stdout);
    fwrite(otherdata, sizeof(char), diafora, stdout);//τυπώνουμε τα χεντερς με fwrite που δουλεύει όπως η fread 

    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            for (int k = 0; k < 3; k++) { // τυπώνουμε τα πίξελ κάθες γραμμής 
                putchar(rotated[i][j][k]);
            }
        }
        for (int k = 0; k < padding; k++) {// και έπειτα το κατάλληλο πάντινγκ στο τέλος
            putchar('\0');
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);

    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            free(rotated[i][j]);
        }
        free(rotated[i]);
    }
    free(rotated);

    free(otherdata);
    free(pixels);
// τέλος αποδεσμεύουμε όλη την μνήμη που χρησιμοποιήσαμε
    return 0;
}
