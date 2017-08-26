package up.teste.cadastro.armazenamento;


import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.DatabaseErrorHandler;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import java.util.ArrayList;

import up.teste.cadastro.modelos.Usuario;

public class ArmazenamentoUsuario extends SQLiteOpenHelper{

    private static String nomeTabela = "Tabela_Usuarios";
    private static int versao = 1;

    private static String colunaUsuarioNome = "colunaUsuarioNome";
    private static String colunaUsuarioSobrenome = "colunaUsuarioSobrenome";
    private static String colunaUsuarioNasc = "colunaUsuarioNasc";
    private static String colunaUsuarioGenero = "colunaUsuarioGenero";
    private static String colunaUsuarioImagem = "colunaUsuarioImagem";

    private static String criarTabela = "CREATE TABLE "+
                                            nomeTabela               + " ( " +
                                            colunaUsuarioNome        + " TEXT, " +
                                            colunaUsuarioSobrenome   + " TEXT, " +
                                            colunaUsuarioGenero      + " TEXT, " +
                                            colunaUsuarioImagem      + " TEXT, " +
                                            colunaUsuarioNasc        + " TEXT );";


    public ArmazenamentoUsuario(Context context) {
        super(context, nomeTabela, null, versao);
    }

    @Override
    public void onCreate(SQLiteDatabase sqLiteDatabase) {
        sqLiteDatabase.execSQL(criarTabela);
    }

    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int oldVersion, int newVersion) {
        sqLiteDatabase.execSQL("DROP TABLE IF EXISTS " + nomeTabela + ";");
        onCreate(sqLiteDatabase);
    }

    public ArrayList<Usuario> getTodosUsuarios(){

        ArrayList<Usuario> usuarios = new ArrayList<>();

        SQLiteDatabase sqLiteDatabase = getReadableDatabase();

        String[] colunas = {colunaUsuarioImagem, colunaUsuarioNasc, colunaUsuarioNome, colunaUsuarioGenero, colunaUsuarioSobrenome};


        Cursor cursor = sqLiteDatabase.query(nomeTabela, colunas, null, null, null, null, null, null);

        cursor.moveToFirst();

        while(!cursor.isAfterLast()){

            Usuario usuario = new Usuario();

            usuario.setNome(cursor.getString(cursor.getColumnIndex(colunaUsuarioNome)));
            usuario.setSobrenome(cursor.getString(cursor.getColumnIndex(colunaUsuarioSobrenome)));
            usuario.setDataNascimento(cursor.getString(cursor.getColumnIndex(colunaUsuarioNasc)));
            usuario.setGenero(cursor.getString(cursor.getColumnIndex(colunaUsuarioGenero)));
            usuario.setEnderecoImagem(cursor.getString(cursor.getColumnIndex(colunaUsuarioImagem)));

            usuarios.add(usuario);

            cursor.moveToNext();

        }

        sqLiteDatabase.close();

        return usuarios;
    }

    public void salvarUsuario(Usuario usuario){

        SQLiteDatabase sqLiteDatabase= getWritableDatabase();

        ContentValues contentValues = new ContentValues();

        contentValues.put(colunaUsuarioNome, usuario.getNome());
        contentValues.put(colunaUsuarioSobrenome, usuario.getSobrenome());
        contentValues.put(colunaUsuarioGenero, usuario.getGenero());
        contentValues.put(colunaUsuarioImagem, usuario.getEnderecoImagem());
        contentValues.put(colunaUsuarioNasc, usuario.getDataNascimento());

        sqLiteDatabase.insert(nomeTabela, null, contentValues);

        sqLiteDatabase.close();

    }



}
