#include <stdio.h>
#include <stdlib.h>

int main() {
  // Read Origanl Image Dimensions
  int img_height, img_width;

  scanf("%d %d", &img_width, &img_height);

  // Create Original Image
  int **original_image = (int **) calloc(img_height, sizeof(int *));

  for (int i = 0; i < img_height; i++)
    original_image[i] = calloc(img_width, sizeof(int));

  // Read Original Image
  for (int i = 0; i < img_height; i++)
    for (int j = 0; j < img_width; j++)
      scanf("%d", &original_image[i][j]);

  // Read Border Width
  int border_width;

  scanf(" %d", &border_width);

  // Create New Image
  int **new_image = (int **) calloc(img_height + 2 * border_width, sizeof(int *));

  for (int i = 0; i < img_height + 2 * border_width; i++)
    new_image[i] = calloc(img_width + 2 * border_width, sizeof(int));

  // Insert New Image
  for (int i = 0; i < img_height; i++)
    for (int j = 0; j < img_width; j++)
      new_image[i + border_width][j + border_width] = original_image[i][j];

  // Print New Image
  for (int i = 0; i < img_height + 2 * border_width; i++) {
    for (int j = 0; j < img_width + 2 * border_width; j++)
      printf("%d ", new_image[i][j]);
    printf("\n"); 
  }

  printf("\n");

  // Print Original Image
  for (int i = 0; i < img_height; i++) {
    for (int j = 0; j < img_width; j++)
      printf("%d ", original_image[i][j]);
    printf("\n"); 
  }

  // Free Memory
  for (int i = 0; i < img_height; i++)
    free(original_image[i]);
  free(original_image);

  for (int i = 0; i < img_height + 2 * border_width; i++)
    free(new_image[i]);
  free(new_image);  

  return 0;
}