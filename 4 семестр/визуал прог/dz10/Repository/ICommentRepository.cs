
using dz10.Model;

namespace WebApplication2.Repositories;

public interface ICommentRepository
{
    IEnumerable<Comment> GetAll();      
    Comment GetById(int id);            
    Comment Add(Comment comment);      
    Comment Update(int id, Comment comment); 
    bool Delete(int id);
}