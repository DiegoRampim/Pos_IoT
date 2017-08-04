package up.teste.jogodavelha;

import android.content.DialogInterface;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{


    private Button button1;
    private Button button2;
    private Button button3;
    private Button button4;
    private Button button5;
    private Button button6;
    private Button button7;
    private Button button8;
    private Button button9;
    private Button buttonNovo;
    private TextView textView;


    private char jogador = 'X';

    private char[][] matriz = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button1 = (Button) findViewById(R.id.button1);
        button2 = (Button) findViewById(R.id.button2);
        button3 = (Button) findViewById(R.id.button3);
        button4 = (Button) findViewById(R.id.button4);
        button5 = (Button) findViewById(R.id.button5);
        button6 = (Button) findViewById(R.id.button6);
        button7 = (Button) findViewById(R.id.button7);
        button8 = (Button) findViewById(R.id.button8);
        button9 = (Button) findViewById(R.id.button9);
        buttonNovo = (Button) findViewById(R.id.buttonNovo);

        textView = (TextView) findViewById(R.id.textView);

        button1.setOnClickListener(this);
        button2.setOnClickListener(this);
        button3.setOnClickListener(this);
        button4.setOnClickListener(this);
        button5.setOnClickListener(this);
        button6.setOnClickListener(this);
        button7.setOnClickListener(this);
        button8.setOnClickListener(this);
        button9.setOnClickListener(this);
        buttonNovo.setOnClickListener(this);

    }

    @Override
    protected void onRestart() {
        super.onRestart();
        this.recreate();
    }


    @Override
    public void onClick(View view) {

        Button button = (Button) view;

        if(view.getId() == R.id.buttonNovo){
            Toast.makeText(getApplicationContext(), "O jogo vai recomeçar!", Toast.LENGTH_SHORT).show();
            this.recreate();
        }

        button.setText(String.valueOf(jogador));
        button.setEnabled(false);

        switch (view.getId()){

            case R.id.button1:
                    matriz[0][0] = jogador;
               break;

            case R.id.button2:
                    matriz[0][1] = jogador;
                break;

            case R.id.button3:
                    matriz[0][2] = jogador;
                break;

            case R.id.button4:
                matriz[1][0] = jogador;
                break;

            case R.id.button5:
                matriz[1][1] = jogador;
                break;

            case R.id.button6:
                matriz[1][2] = jogador;
                break;

            case R.id.button7:
                matriz[2][0] = jogador;
                break;

            case R.id.button8:
                matriz[2][1] = jogador;
                break;

            case R.id.button9:
                matriz[2][2] = jogador;
                break;

        }

        buscaVencedor(jogador);

        if(jogador == 'X'){
            jogador = 'O';
        }else{
            jogador = 'X';
        }

        textView.setText("Jogador " + String.valueOf(jogador));


    }

    public void buscaVencedor(char jogador){

        boolean ganhou = false;

        for(int x = 0; x <= 2; x++){
            if(matriz[x][0] == matriz[x][1] && matriz[x][0] == matriz[x][2] ){
                //Ganhou
                ganhou = true;
            }

            if(matriz[0][x] == matriz[1][x] && matriz[0][x] == matriz[2][x] ){
                //Ganhou
                ganhou = true;
            }
        }

        if(matriz[0][0] == matriz[1][1] && matriz[0][0] == matriz[2][2] ){
            //Ganhou
            ganhou = true;
        }

        if(matriz[0][2] == matriz[1][1] && matriz[0][2] == matriz[2][0] ){
            //Ganhou
            ganhou = true;
        }

        if(ganhou){
            //Toast.makeText(getApplicationContext(), "Jogador " + String.valueOf(jogador) + " ganhou!", Toast.LENGTH_LONG).show();

            Intent intent = new Intent(MainActivity.this, GanhouActivity.class);
            intent.putExtra("jogador", String.valueOf(jogador));
            startActivity(intent);
        }

    }


}
