bool isalpha(unsigned char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ){
        return true;
    }
    else {
        return false;
    }
}

unsigned char tolower(unsigned char c) {
    if (c >= 'A' && c <= 'Z' ) {
        c = 'a' + (c - 'A');
    }
    return c;
    
}
