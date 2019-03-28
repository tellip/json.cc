#pragma once

#define JSON_COMMA ,

#define JSON_DELETE(P) {if(P) delete P; P=nullptr;}
#define JSON_DELETE_S(P) {if(P) delete[] P; P=nullptr;}
