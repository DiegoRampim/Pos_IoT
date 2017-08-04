package up.teste.cadastro;

import android.Manifest;
import android.app.Activity;
import android.app.DatePickerDialog;
import android.app.DialogFragment;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.DataSetObserver;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Environment;
import android.provider.MediaStore;
import android.support.annotation.NonNull;
import android.support.design.widget.Snackbar;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ListAdapter;
import android.widget.Spinner;
import android.widget.TextView;

import java.io.File;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;


import up.teste.cadastro.adaptadores.AdaptadorGenero;
import up.teste.cadastro.fragmentos.DialogoData;

public class CadastroActivity extends AppCompatActivity {

    private EditText editTextNome;
    private EditText editTextSobrenome;
    private Spinner spinnerGenero;
    private Button buttonSalvar;
    private ImageView imageView;
    private TextView textViewDataNascimento;

    private String diretorioImagem;

    private ArrayList<String> generos;



    private final int codigoRequisicaoImagem = 1001;
    private final int codigoPermissao = 1002;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cadastro);

        editTextNome = (EditText) findViewById(R.id.editTextNome);
        editTextSobrenome = (EditText) findViewById(R.id.editTextSobrenome);
        spinnerGenero = (Spinner) findViewById(R.id.spinnerGenero);
        buttonSalvar = (Button) findViewById(R.id.buttonSalvar);
        imageView = (ImageView) findViewById(R.id.imageView);
        textViewDataNascimento = (TextView) findViewById(R.id.textViewDataNascimento);

        generos = new ArrayList<>();
        generos.add("Masculino");
        generos.add("Feminino");
        generos.add("Não se aplica");

        AdaptadorGenero adaptadorGenero = new AdaptadorGenero(generos);

        spinnerGenero.setAdapter(adaptadorGenero);


        textViewDataNascimento.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                DialogoData dialogoData = new DialogoData();
                FragmentManager fragmentManager = getSupportFragmentManager();
                dialogoData.show(fragmentManager, "tag");
            }
        });

        imageView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                if(!hasPermition()){
                    return;
                }

                Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);

                File arquivoImagem = getImageFile();

                if(arquivoImagem != null){

                    diretorioImagem = arquivoImagem.getAbsolutePath();

                    //String diretorioImagem = arquivoImagem.getAbsolutePath();

                    intent.putExtra(MediaStore.EXTRA_OUTPUT, Uri.fromFile(arquivoImagem));

                    startActivityForResult(intent, codigoRequisicaoImagem);

                }



            }
        });

    }

    private File getImageFile(){

        String complementoNome = new SimpleDateFormat("yyMMdd-HHmmss").format(new Date());

        String nomeDoArquivo = "imagem" + complementoNome ;

        File estrutauraImagens = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES);

        try{


            return File.createTempFile(nomeDoArquivo, ".jpg", estrutauraImagens);
        }catch (Exception e){

            Log.v("APP ",e.getLocalizedMessage());
            return null;
        }

    }

    private boolean hasPermition(){

        if(ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED){
            return true;

        }else{

            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, codigoPermissao);

            return false;
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        if(codigoPermissao == requestCode && grantResults[0] == PackageManager.PERMISSION_GRANTED){}

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if(codigoRequisicaoImagem == requestCode && resultCode == RESULT_OK){

            setImagemUsuario();

        }
    }


    private void setImagemUsuario(){

        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inJustDecodeBounds = true;

        BitmapFactory.decodeFile(diretorioImagem, options);

        options.inJustDecodeBounds = false;

        int escalaLargura = imageView.getWidth()/options.outWidth;
        int escalaAltura = imageView.getHeight()/options.outHeight;

        //options.inSampleSize = Math.min(escalaAltura, escalaLargura);

        options.inSampleSize = 3;

        Bitmap imagem = BitmapFactory.decodeFile(diretorioImagem, options);

        imageView.setImageBitmap(imagem);

    }

}
