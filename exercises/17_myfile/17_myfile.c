#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_elf_type(uint16_t e_type) {
  const char *type_str;
  switch (e_type) {
    case ET_REL:
      type_str = "Relocatable";
      break;
    case ET_EXEC:
      type_str = "Executable";
      break;
    case ET_DYN:
      type_str = "Shared Object/PIE";
      break;
    default:
      type_str = "Unknown";
      break;
  }
  printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int main(int argc, char *argv[]) {
  char filepath[2][256] = {
    "./17_myfile.o",
    "./17_myfile",
  };

  Elf64_Ehdr ehdr;

  for (int i = 0; i < 2; ++i) {
    FILE *file = fopen(filepath[i], "rb");
    if (file == NULL) {
      printf("无法打开文件: %s\n", filepath[i]);
      continue;
    }

    size_t n = fread(&ehdr, 1, sizeof(Elf64_Ehdr), file);

    if (n != sizeof(Elf64_Ehdr)) {
      fprintf(stderr, "Error: failed to read ELF header (%zu bytes)\n", n);
      fclose(file);
      continue;
    }

    if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0) {
      fprintf(stderr, "Error: not a valid ELF file\n");
      fclose(file);
      continue;
    }

    if (ehdr.e_ident[EI_CLASS] != ELFCLASS64) {
      fprintf(stderr, "Warning: not a 64-bit ELF (class=%d)\n",
              ehdr.e_ident[EI_CLASS]);
    }

    print_elf_type(ehdr.e_type);

    fclose(file);

  }
  
  return 0;
}
