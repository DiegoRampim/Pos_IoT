package up.teste.jogodavelha;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class GanhouActivity extends AppCompatActivity {

    private TextView textViewGanhou;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ganhou);

        textViewGanhou = (TextView) findViewById(R.id.textViewGanhou);

        Intent intent = getIntent();


        textViewGanhou.setText("Parabens Jogador " + intent.getStringExtra("jogador"));

    }
}
