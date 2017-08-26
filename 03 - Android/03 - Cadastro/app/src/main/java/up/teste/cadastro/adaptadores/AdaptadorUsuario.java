package up.teste.cadastro.adaptadores;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.zip.Inflater;

import up.teste.cadastro.R;
import up.teste.cadastro.modelos.Usuario;


public class AdaptadorUsuario extends BaseAdapter {

    private ArrayList<Usuario> usuarios;
    private TextView usuarioNome;
    private TextView usuarioSobrenome;
    private TextView usuarioGenero;
    private TextView usuarioNascimento;
    private ImageView usuarioImagem;

    public AdaptadorUsuario(ArrayList<Usuario> usuarios) {
        this.usuarios = usuarios;
    }

    @Override
    public int getCount() {
        return usuarios.size();
    }

    @Override
    public Object getItem(int i) {
        return usuarios.get(i);
    }

    @Override
    public long getItemId(int i) {
        return 0;
    }

    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {

        Usuario usuario = new Usuario();
        usuario = usuarios.get(i);


        if(view == null){
            LayoutInflater inflater = LayoutInflater.from(viewGroup.getContext());
            view = inflater.inflate(R.layout.item_usuario, viewGroup, false);
        }

        usuarioNome = (TextView) view.findViewById(R.id.textViewUsuarioNome);
        usuarioSobrenome = (TextView) view.findViewById(R.id.textViewUsuarioSobrenome);
        usuarioGenero = (TextView) view.findViewById(R.id.textViewUsuarioGenero);
        usuarioNascimento = (TextView) view.findViewById(R.id.textViewUsuarioNascimento);
        usuarioImagem = (ImageView) view.findViewById(R.id.imageViewUsuario);

        usuarioNome.setText(usuario.getNome());
        usuarioSobrenome.setText(usuario.getSobrenome());
        usuarioNascimento.setText(usuario.getDataNascimento());
        usuarioGenero.setText(usuario.getGenero());

        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inSampleSize = 4;

        Bitmap bitmap = BitmapFactory.decodeFile(usuario.getEnderecoImagem(), options);
        usuarioImagem.setImageBitmap(bitmap);

        return view;
    }

 }
