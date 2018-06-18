//
// Created by aa on 2015/10/2.
//

#pragma once

#define JSON_COMMA ,

#define JSON_DELETE(P) {if(P) delete P; P=NULL;}
#define JSON_DELETE_S(P) {if(P) delete[] P; P=NULL;}
