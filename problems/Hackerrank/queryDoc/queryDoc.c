#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

typedef char *word;

typedef word *sentence;

typedef sentence *paragraph;

typedef paragraph *document;

word kth_word_in_mth_sentence_of_nth_paragraph(document document, int k, int m, int n);
sentence kth_sentence_in_mth_paragraph(document document, int k, int m);
paragraph kth_paragraph(document document, int k);
document get_document(word text);
char *get_input_text();
void print_word(word word);
void print_sentence(char **sentence);
void print_paragraph(paragraph paragraph);


word kth_word_in_mth_sentence_of_nth_paragraph(document document, int k, int m, int n)
{
    return document[n - 1][m - 1][k - 1];
}

sentence kth_sentence_in_mth_paragraph(document document, int k, int m)
{
    return document[m - 1][k - 1];
}

paragraph kth_paragraph(document document, int k)
{
    return document[k - 1];
}

document get_document(word text)
{
    int char_count = 0;
    int paragraphs = 0;
    int sentences[MAX_PARAGRAPHS] = {0};
    int words[MAX_PARAGRAPHS][MAX_CHARACTERS] = {0};

    for (char *str = NULL, c; (c = *str++); )
    {
        if (c == ' ')
            words[paragraphs][sentences[paragraphs]]++;
        if (c == '.')
            sentences[paragraphs]++;
        if (c == '\n')
            paragraphs++;
        char_count++;
    }

    document doc = malloc(paragraphs * sizeof(paragraph));
    for (int i = 0; i < paragraphs; i++)
    {
        doc[i] = malloc(MAX_PARAGRAPHS * sizeof(sentence));
        for (int j = 0; j < MAX_PARAGRAPHS; j++)
        {
            doc[i][j] = malloc(sentences[j] * sizeof(word));
            for (int k = 0; k < words[i][j]; k++)
                doc[i][j][k] = malloc(words[i][j] * sizeof(char));
        }
    }

    int wrd_index = 0, sentn_index = 0, para_index = 0;
    for (char *str = NULL, c; (c = *str++); )
    {
        if (c == ' ' || c == '.' || c == '\n')
        {
            doc[para_index][sentn_index][para_index] = "\0";
            wrd_index = 0;
            if (c == '.')
                sentn_index++;
            else if (c == '\n')
            {
                para_index++;
                sentn_index = 0;
            }
        }
        else
        {
            doc[para_index][sentn_index][wrd_index] = malloc();
            doc[para_index][sentn_index][wrd_index][1] = '\0';
            wrd_index++;
        }
    }

    return doc;
}



char *get_input_text()
{
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++)
    {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char *returnDoc = (char *) malloc((strlen(doc) + 1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(word word)
{
    printf("%s", word);
}

void print_sentence(char **sentence)
{
    int word_count;
    scanf("%d", &word_count);
    for (int i = 0; i < word_count; i++)
    {
        printf("%s", sentence[i]);
        if (i != word_count - 1)
            printf(" ");
    }
}

void print_paragraph(paragraph paragraph)
{
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++)
    {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main()
{
    char *text = get_input_text();
    char ****document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--)
    {
        int type;
        scanf("%d", &type);

        if (type == 3)
        {
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char *word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2)
        {
            int k, m;
            scanf("%d %d", &k, &m);
            char **sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else
        {
            int k;
            scanf("%d", &k);
            char ***paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }
}



// Will figure out how I fucked up in this eventually
/*
document get_document(word text)
{
    word *words = NULL;
    sentence *sentences = NULL;
    paragraph *paragraphs = NULL;
    int words_count = 0, words_in_para = 0, sentences_count = 0, paragraphs_count = 0;

    for (int i = 0, w = 0; text[i] != '\0'; i++, w++)
    {
        // Check for space, period, or newline
        if (text[i] == ' ' || text[i] == '.' || text[i] == '\n' || text[i] == '\0')
        {

            // Allocate memory for the current word
            if (text[i] == '.')
            char *string = malloc((w + 1) * sizeof(char));
            string[w] = '\0';

            // Copy characters to the current word
            for (int j = 0; j < w; j++)
                string[j] = text[i - w + j];

            // Allocate memory for the words array and copy the current word
            if (words == NULL)
                words = malloc((words_count + 1) * sizeof(word));
            else
                words = realloc(words, (words_count + 1) * sizeof(word));

            words[words_count] = malloc((w + 1) * sizeof(char));
            strcpy(words[words_count++], string);
            w = 0;  // Reset word length
        }

        // Check for a period to end a sentence
        if (text[i] == '.' || text[i] == '\0')
        {
            // Allocate memory for the sentences array and copy the words
            if (sentences == NULL)
                sentences = malloc((sentences_count + 1) * sizeof(sentence));
            else
                sentences = realloc(sentences, (sentences_count + 1) * sizeof(sentence));

            sentences[sentences_count] = malloc(words_count * sizeof(word));

            // Copy words to the current sentence and free memory for individual words
            for (int j = 0; j < words_count; j++)
            {
                sentences[sentences_count][j] = malloc((strlen(words[j]) + 1) * sizeof(char));
                strcpy(sentences[sentences_count][j], words[j]);
                print_word(sentences[sentences_count][j]);
                free(words[j]);
            }

            print_sentence(sentences[sentences_count]);
            sentences_count++;
            words_in_para += words_count;
            words_count = 0;
        }

        // Check for a newline to end a paragraph
        if (text[i] == '\n' || text[i] == '\0')
        {
            // Allocate memory for the paragraphs array and copy the sentences
            if (paragraphs == NULL)
                paragraphs = malloc((paragraphs_count + 1) * sizeof(paragraph));
            else
                paragraphs = realloc(paragraphs, (paragraphs_count + 1) * sizeof(paragraph));

            paragraphs[paragraphs_count] = malloc(sentences_count * sizeof(sentence));

            // Copy sentences to the current paragraph
            for (int j = 0; j < sentences_count; j++)
            {
                paragraphs[paragraphs_count][j] = malloc(words_count * sizeof(word));

                for (int k = 0; k < words_in_para; k++)
                {
                    paragraphs[paragraphs_count][j][k] = malloc((strlen(sentences[j][k]) + 1) * sizeof(char));
                    strcpy(paragraphs[paragraphs_count][j][k], sentences[j][k]);
                    free(sentences[j][k]);
                }
                free(sentences[j]);
            }

            print_paragraph(paragraphs[paragraphs_count]);
            paragraphs_count++;
            sentences_count = 0;
            words_in_para = 0;
        }
    }

    // Free memory for the remaining words, sentences, and the words array
    free(words);
    free(sentences);

    // Return the paragraphs array
    return paragraphs;
}
*/
