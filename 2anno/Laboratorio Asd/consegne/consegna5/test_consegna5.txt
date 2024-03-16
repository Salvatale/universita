int main(int argc, char **argv) {
    int i, test;

    srand((unsigned)time(NULL));

    if (parse_cmd(argc, argv))
        return 1;

    ifstream file("test.cpp");

    file.seekg(0,std::ios::end);
    std::streampos filesize = file.tellg();
    file.seekg(0,std::ios::beg);

    const int s1 = filesize;
    const int s2 = filesize;

    char *str1 = new char[filesize+1];
    char *str2 = new char[filesize+1];

    file.read(str1,filesize);
    file.read(str2,filesize);

    str1[filesize] = '\0';
    str2[filesize] = '\0';

    cout << "Dim: " << filesize << endl;

    // const int s1 = strlen(temp1);
    // const int s2 = strlen(temp2);

    // char *str1;
    // char *str2;

    // str1 = new char[s1];
    // str2 = new char[s2];

    // for (i = 0; i < s1; i++) {
    //     str1[i] = temp1[i];
    // }
    // for (i = 0; i < s2; i++) {
    //     str2[i] = temp2[i];
    // }

    M = new int *[s1 + 1];
    for (i = 0; i < s1 + 1; i++)
        M[i] = new int[s2 + 1];

    for (int i = 0; i < s1 + 1; i++)
        M[i][0] = 0;
    for (int j = 0; j < s2 + 1; j++)
        M[0][j] = 0;

    for (int i = 1; i < s1 + 1; i++)
        for (int j = 1; j < s2 + 1; j++) {

            /// sottostringa (con maiuscole/minuscole)
            int match = is_match_consegna(str1[i - 1], str2[j - 1]);

            // /// calcolo costo sottostringa (con maiuscole/minuscole)
            // int match = 0;
            // if (str1[i - 1] == str2[j - 1])
            //     match = 1;
            // else {
            //     char temp1 = str1[i - 1];
            //     if (temp1 >= 'a' && temp1 <= 'z')
            //         temp1 -= abs('A' - 'a');
            //     char temp2 = str2[j - 1];
            //     if (temp2 >= 'a' && temp2 <= 'z')
            //         temp2 -= abs('A' - 'a');
            //     if (temp1 == temp2)
            //         match = 1;
            // }

            /// sottosequenza
            if (match) { // match
                         /// M(i, j) ← 1 + M(i − 1, j − 1)
                M[i][j] = match + M[i - 1][j - 1];
            } else { // mismatch
                // M(i, j) ← max(M(i − 1, j), M(i, j − 1))
                int max = M[i - 1][j];
                if (max < M[i][j - 1])
                    max = M[i][j - 1];
                M[i][j] = max;
            }

            /// sottostringa
            // if (match) { // match
            //              /// M(i, j) ← 1 + M(i − 1, j − 1)
            //     M[i][j] = 1 + M[i - 1][j - 1];
            // } else { // mismatch
            //     M[i][j] = 0;
            // }
        }

    for (int i = 0; i < s1 + 1; i++) {

        // if (i == 0) {
        //     printf("   ");
        //     for (int j = 0; j < s2 + 1; j++)
        //         printf("%d ", j);
        //     printf("\n");
        // }

        printf("%2d: ", i);

        for (int j = 0; j < s2 + 1; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    i = s1;
    int j = s2;

    // ricostruzione sottosequenza
    while (i > 0 || j > 0) {
        // printf("posizione: %d %d\n", i, j);
        if (i > 0 && j > 0 && is_match_consegna(str1[i - 1],str2[j - 1])) {
            printf("%c", str1[i - 1]);
            i--;
            j--;
        } else {
            // if M(i,j) = M(i−1,j) then i ← i−1 else j ← j−1
            if (i > 0 && M[i][j] == M[i - 1][j])
                i--;
            else
                j--;
        }
    }
    printf("\n");

    return 0;
}
