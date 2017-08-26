package up.teste.cadastro;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ListView;
import android.widget.Toast;

import java.util.ArrayList;

import up.teste.cadastro.adaptadores.AdaptadorUsuario;
import up.teste.cadastro.armazenamento.ArmazenamentoUsuario;
import up.teste.cadastro.modelos.Usuario;

public class MainActivity extends AppCompatActivity {

    private final int retornoCadastro = 1000;
    private ListView listViewUsuarios;
    private ArrayList<Usuario> usuarios;
    private AdaptadorUsuario adaptadorUsuario;
    private ArmazenamentoUsuario armazenamentoUsuario;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        armazenamentoUsuario = new ArmazenamentoUsuario(this);

        usuarios = armazenamentoUsuario.getTodosUsuarios();

        listViewUsuarios = (ListView) findViewById(R.id.listViewUsuarios);


        adaptadorUsuario = new AdaptadorUsuario(usuarios);
        listViewUsuarios.setAdapter(adaptadorUsuario);


    }

     @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {

        int id = item.getItemId();

        if (id == R.id.action_add) {

            Intent intent = new Intent(MainActivity.this, CadastroActivity.class);
            startActivityForResult(intent, retornoCadastro);
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if(requestCode == retornoCadastro && resultCode == RESULT_OK){

            Usuario usuario = new Usuario();

            usuario = (Usuario) data.getSerializableExtra("usuario");

            armazenamentoUsuario.salvarUsuario(usuario);

            usuarios.add(usuario);

            adaptadorUsuario.notifyDataSetChanged();

        }
    }
}
